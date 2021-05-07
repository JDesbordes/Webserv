#include "Route.hpp"

Route::Route() : _root(""), _autoindex(true), _cgi_extension(""), _cgi_path(""), _client_max_body_size(1000000000) {}
Route::Route(const Route &o)
    : _root(o._root), _method(o._method), _autoindex(o._autoindex), _index(o._index), _cgi_extension(o._cgi_extension), _cgi_path(o._cgi_path) , _client_max_body_size(o._client_max_body_size) {}
Route &Route::operator=(const Route &o)
{
    if (this == &o) return (*this);
    this->~Route();
    return *new(this) Route(o);
}

void Route::setRoot(std::string root) { _root = root; }
void Route::addMethod(t_method_type type) { _method.push_back(type); }
void Route::setAutoIndex(bool autoindex) { _autoindex = autoindex; }
void Route::addIndex(std::string filename) { _index.push_back(filename); }
void Route::setCGIExtension(std::string ext) { _cgi_extension = ext; }
void Route::setCGIPath(std::string path) { _cgi_path = path; }
void Route::setClientMaxBodySize(size_t size) { _client_max_body_size = size; }

std::string &Route::getRoot() { return (_root); }
std::vector<t_method_type> &Route::getMethod() { return (_method); }
bool &Route::getAutoIndex() { return (_autoindex); }
std::vector<std::string> &Route::getIndex() { return (_index); }
std::string &Route::getCGIExtension() { return (_cgi_extension); }
std::string &Route::getCGIPath() { return (_cgi_path); }
size_t &Route::getClientMaxBodySize() { return (_client_max_body_size); }

void Route::debug()
{
    std::cout << "root: " << _root << std::endl;
    std::cout << "method: " << std::endl;
    for (size_t i = 0; i < _method.size(); i++)
        if (_method[i] == GET)          std::cout << "\tGET" << std::endl;
        else if (_method[i] == HEAD)    std::cout << "\tHEAD" << std::endl;
        else if (_method[i] == POST)    std::cout << "\tPOST" << std::endl;
        else if (_method[i] == PUT)     std::cout << "\tPUT" << std::endl;
        else if (_method[i] == DELETE)  std::cout << "\tDELETE" << std::endl;
        else if (_method[i] == CONNECT) std::cout << "\tDELETE" << std::endl;
        else if (_method[i] == OPTIONS) std::cout << "\tOPTIONS" << std::endl;
        else if (_method[i] == PATCH)   std::cout << "\tPATCH" << std::endl;
        else                            std::cout << "\tTRACE" << std::endl;
    std::cout << "autoindex: " << _autoindex << std::endl;
    std::cout << "index: " << std::endl;
    for (size_t i = 0; i < _index.size(); i++)
        std::cout << "\t" << _index[i] << std::endl;
    std::cout << "client_max_body_size: " << _client_max_body_size << std::endl;
    std::cout << "CGI extension: " << _cgi_extension << std::endl;
    std::cout << "CGI path: " << _cgi_path << std::endl;
}

Route::~Route() {}