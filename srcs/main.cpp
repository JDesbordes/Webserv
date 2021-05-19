#include "global.hpp"

void *StartWorker(void *args) {
    Client              *clients[FD_SETSIZE];
    bool                all_receive[FD_SETSIZE];
    bool                close_conn[FD_SETSIZE];
    char                buffer[RECV_BUFFER_SIZE];
    fd_set              master_set, working_set;
    int                 len, rc;
    int                 desc_ready;
    int                 max_sd = FD_SETSIZE, new_sd;

    t_worker            *worker = static_cast<t_worker*>(args);
    char **env      =   worker->env;
    Server *server  =   worker->serv;

    FD_ZERO(&master_set);
    FD_SET(server_socket, &master_set);

    for (int i = 0; i < FD_SETSIZE; i++)
    {
        all_receive[i] = false;
        close_conn[i] = false;
    }

    int count = 0;
    while (true)
    {
        memcpy(&working_set, &master_set, sizeof(master_set));
        Debug::info("Waiting on select()...");
        rc = select(FD_SETSIZE, &working_set, NULL, NULL, NULL);
        if (rc < 0)
        {
            Debug::error("select() failed [" + std::string(strerror(errno)) + "]");
            break;
        }
        Debug::info("RC ", rc);
        desc_ready = rc;
        for (int i = 0; i <= max_sd && desc_ready > 0; ++i)
        {
            if (FD_ISSET(i, &working_set))
            {
                desc_ready -= 1;
                if (i == server_socket)
                {
                    Debug::checkpoint("Listening socket is readable Count:", count);
                    do
                    {
                        new_sd = accept(server_socket, NULL, NULL);
                        if (new_sd < 0)
                        {
                            if (errno != EWOULDBLOCK)
                            {
                                Debug::error("accept() failed [" + std::string(strerror(errno)) + "]");
                                exit(1);
                            }
                            break;
                        }
                        else {
                            Debug::checkpoint("New incoming connection - ", new_sd);
                            FD_SET(new_sd, &master_set);
                            clients[new_sd] = new Client(new_sd, env, server);
                            count++;
                        }
                    } while (new_sd != -1);
                }
                else
                {
                    Debug::checkpoint("Descriptor is readable - Count:", count);
                    while (true)
                    {
                        if (!all_receive[i])
                        {
                            rc = recv(i, buffer, sizeof(buffer), 0);
                            if (rc < 0)
                            {
                                if (errno != EWOULDBLOCK && errno != EAGAIN)
                                {
                                    Debug::warning("recv() failed [" + std::string(strerror(errno)) + "]");
                                    close_conn[i] = true;
                                    break;
                                }
                                // else
                                //     Debug::warning("send() failed [" + std::string(strerror(errno)) + "]");
                            }
                            else
                            {
                                len = rc;
                                //Debug::info("bytes received: [" + Debug::escapestr(std::string(buffer, len)) + "]", len);
                                clients[i]->append(std::string(buffer, len));

                                if (clients[i]->hasFinishedReading())
                                {
                                    clients[i]->process();
                                    all_receive[i] = true;
                                }
                            }
                        }
                        if (all_receive[i])
                        {
                            Debug::checkpoint("Send : ", clients[i]->getResponseLength());
                            rc = send(i, clients[i]->getResponse(), clients[i]->getResponseLength(), 0);
                            if (rc < 0)
                            {
                                if (errno != EWOULDBLOCK && errno != EAGAIN)
                                {
                                    Debug::warning("send() failed [" + std::string(strerror(errno)) + "]");
                                    close_conn[i] = true;
                                    break;
                                }
                                else
                                {
                                    //Debug::warning("send() failed [" + std::string(strerror(errno)) + "]");
                                    close_conn[i] = true;
                                }
                            }
                            else {
                                clients[i]->substract(rc); 
                                if (clients[i]->hasFinishedSending())
                                {
                                    Debug::checkpoint("Connection closed");
                                    close_conn[i] = true;
                                    break;
                                }
                            }
                        }
                    }

                    if (close_conn[i])
                    {
                        close(i);
                        FD_CLR(i, &master_set);
                        delete clients[i];
                        all_receive[i] = false;
                        close_conn[i] = false;
                        Debug::checkpoint("Close FD");
                    }
                }
            }
        }
    }
    pthread_exit(NULL);
}

void RunServer(Server server, char **env)
{
    int                     rc, on = 1;
    struct sockaddr_in      addr;
    //pthread_t               *workers = (pthread_t *)malloc(WORKERS * sizeof(pthread_t));
    t_worker                data;

    addr.sin_family = AF_INET;
	addr.sin_port = htons(server.getPort());
	addr.sin_addr.s_addr = inet_addr(server.getHost().c_str());

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        Debug::error("socket() failed [" + std::string(strerror(errno)) + "]");
        exit(-1);
    }

    signal(SIGINT, int_handler);
    rc = setsockopt(server_socket, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on));
    if (rc < 0)
    {
        Debug::error("setsockopt() failed [" + std::string(strerror(errno)) + "]");
        close(server_socket);
        exit(-1);
    }

    rc = noblock(server_socket);
    if (rc < 0)
    {
        Debug::error("noblock() failed [" + std::string(strerror(errno)) + "]");
        close(server_socket);
        exit(-1);
    }

    rc = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
    if (rc < 0)
    {
        Debug::error("bind() failed [" + std::string(strerror(errno)) + "]");
        close(server_socket);
        exit(-1);
    }

    rc = listen(server_socket, MAX_CONNECTIONS);
    if (rc < 0)
    {
        Debug::error("listen() failed [" + std::string(strerror(errno)) + "]");
        close(server_socket);
        exit(-1);
    }

    data.env = env;
    data.serv = &server;

    for (int i = 0; i < WORKERS; i++)
    {
        pid[i] = fork();
        if (!pid[i]) {
            StartWorker(&data);
        }
    }
    while (true);
}

int main(int ac, char **av, char **env)
{
    if (ac >= 2)
    {
        char *path;
        char buf[2048];

        getcwd(buf, 2048);
        path = ft_strjoin(buf, "/");
        path = ft_strfjoin(path, av[1], 1);
        Parser p(path);
        Debug::checkpoint("Path: " + std::string(path));
        free(path);
        Server s = p.getConfig().at(0);
        RunServer(s, env);
    }
    else
        Debug::error("You need to specified a config path.");
    return (0);
}