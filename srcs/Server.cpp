#include "Server.hpp"

Server::Server() : _port(0), _workers(1) {}

Server::Server(const Server &o)
    :   _port(o._port), _workers(o._workers), _host(o._host), _server_name(o._server_name),
        _error_pages(o._error_pages),
        _route(o._route) {}
Server &Server::operator=(const Server &o)
{
    if (this == &o) return (*this);
    this->~Server();
    return *new(this) Server(o);
}

void Server::setPort(int port) { _port = port; }
void Server::setWorkers(int workers) { _workers = workers; }
void Server::setHost(std::string host) { _host = host; }
void Server::setServerName(std::string server_name) { _server_name = server_name; }
void Server::addErrorPage(int err, std::string page) { _error_pages.insert(std::pair<int, std::string>(err, page)); }
std::map<std::string, Route>::iterator Server::addRoute(std::string path, Route r) { return (_route.insert(std::pair<std::string, Route>(path, r)).first); }

int &Server::getPort() { return (_port); }
int &Server::getWorkers() { return (_workers); }
std::string &Server::getHost() { return (_host); }
std::string &Server::getServerName() { return (_server_name); }
std::map<int, std::string> &Server::getErrorPage() { return (_error_pages); }
std::map<std::string, Route> &Server::getRoute() { return (_route); }

void Server::debug()
{
    std::cout << "port: " << _port << std::endl;
    std::cout << "host: " << _host << std::endl;
    std::cout << "workers: " << _workers << std::endl;
    std::cout << "server_name: " << _server_name << std::endl;
    std::cout << "error_pages: " << std::endl;
    for (std::map<int, std::string>::iterator itr = _error_pages.begin(); itr != _error_pages.end(); itr++)
        std::cout << "\t" << itr->first << "=" << itr->second << std::endl;
    for (std::map<std::string, Route>::iterator itr = _route.begin(); itr != _route.end(); itr++)
    {
        std::cout << "route [" << itr->first << "]:" << std::endl;
        itr->second.debug();
    }
}

Server::~Server() {}