#ifndef SERVER_HPP
#define SERVER_HPP

#include "global.hpp"

class Route;

class Server
{
    public:
        Server();
        Server(const Server &);
        Server &operator=(const Server &);

        void setPort(int port);
        void setHost(std::string host);
        void setServerName(std::string server_name);
        void addErrorPage(int err, std::string page);
        std::map<std::string, Route>::iterator addRoute(std::string, Route);

        int &getPort();
        std::string &getHost();
        std::string &getServerName();
        std::map<int, std::string> &getErrorPage();
        std::map<std::string, Route> &getRoute();

        void debug();

        ~Server();
    private:

        int                                 _port;
        std::string                         _host;
        std::string                         _server_name;
        std::map<int, std::string>          _error_pages;
        std::map<std::string, Route>        _route;
};

#endif // !SERVER_HPP