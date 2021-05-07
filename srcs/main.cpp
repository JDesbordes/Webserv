#include "global.hpp"

void RunServer(Server server, char **env)
{
    Client                  *clients[FD_SETSIZE];
    int                     len, rc, on = 1;
    int                     max_sd, new_sd;
    int                     desc_ready;
    int                     close_conn;
    char                    buffer[RECV_BUFFER_SIZE];
    struct sockaddr_in      addr;
    fd_set                  master_set, working_set;

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

    FD_ZERO(&master_set);
    max_sd = server_socket;
    FD_SET(server_socket, &master_set);

    while (true)
    {
        memcpy(&working_set, &master_set, sizeof(master_set));
        Debug::info("Waiting on select()...");
        rc = select(max_sd + 1, &working_set, NULL, NULL, NULL);
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
                    Debug::checkpoint("Listening socket is readable");
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
                        Debug::checkpoint("New incoming connection - ", new_sd);
                        FD_SET(new_sd, &master_set);
                        if (new_sd > max_sd)
                            max_sd = new_sd;
                        clients[new_sd] = new Client(new_sd, env, &server);
                    } while (new_sd != -1);
                }
                else
                {
                    Debug::checkpoint("Descriptor is readable - ", i);
                    close_conn = false;
                    bool all_receive = false;
                    while (true)
                    {
                        if (!all_receive)
                        {
                            rc = recv(i, buffer, sizeof(buffer), 0);
                            if (rc < 0)
                            {
                                if (errno != EWOULDBLOCK)
                                {
                                    Debug::error("recv() failed [" + std::string(strerror(errno)) + "]");
                                    close_conn = true;
                                }
                                break;
                            }
                            len = rc;
                            //Debug::info("bytes received: [" + Debug::escapestr(std::string(buffer, len)) + "]", len);
                            clients[i]->append(std::string(buffer, len));

                            if (clients[i]->hasFinishedReading())
                            {
                                clients[i]->process();
                                all_receive = true;
                            }
                        }
                        if (all_receive)
                        {
                            Debug::checkpoint("Send : ", clients[i]->getResponseLength());
                            rc = send(i, clients[i]->getResponse(), clients[i]->getResponseLength(), 0);
                            if (rc < 0)
                            {
                                Debug::error("send() failed [" + std::string(strerror(errno)) + "]");
                                close_conn = true;
                                break;
                            }
                            clients[i]->substract(rc); 
                            if (clients[i]->hasFinishedSending())
                            {
                                Debug::checkpoint("Connection closed");
                                close_conn = true;
                                break;
                            }
                        }
                    }

                    if (close_conn)
                    {
                        close(i);
                        FD_CLR(i, &master_set);
                        delete clients[i];
                        Debug::checkpoint("Close FD");
                        if (i == max_sd)
                        {
                            while (FD_ISSET(max_sd, &master_set) == FALSE)
                                max_sd -= 1;
                        }
                    }
                }
            }
        }
    }
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
        Server s = p.getConfig().at(0); // TODO Multi serveur ?
        RunServer(s, env);
    }
    else
        Debug::error("You need to specified a config path.");
    return (0);
}