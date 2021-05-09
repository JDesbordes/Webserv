#include "Client.hpp"

Client::Client() {}
Client::Client(SOCKET socket, char **env, Server *conf) : _socket(socket), _env(env), _conf(conf), _buff(""),
    _from(0), _header(NULL), _header_end(false), _header_size(0), _content(""), _content_end(false), _content_size(0), _chunked(false) {}
Client::Client(const Client &o) : _socket(o._socket), _env(o._env), _conf(o._conf), _buff(o._buff),
    _from(0), _header(NULL), _header_end(false), _header_size(0), _content(""), _content_end(false), _content_size(0), _chunked(false) {}
Client &Client::operator=(const Client &o) {
    _socket = o._socket;
    _env = o._env;
    _buff = o._buff;
    _conf = o._conf;
    _from = o._from;
    _header_end = o._header_end;
    _header = o._header;
    _content_end = o._content_end;
    _header_size = o._header_size;
    _chunked = o._chunked;
    _content_size = o._content_size;
    return (*this);
}

void Client::append(std::string data) {
    _buff += data; 
    Debug::info("buff size: ", _buff.length());
    Debug::info("content size: ", _content.length());
}

bool Client::hasFinishedReading() {
    //Debug::info("Start _buff state [" + Debug::escapestr(_buff) + "]");
    if (!_chunked && !_content_size && _buff.find("\r\n\r\n") != std::string::npos)
    {
        _header_end = true;
        _header_size = _buff.find("\r\n\r\n") + 4;
        _header = new HttpHeader(_buff.substr(0, _header_size));

        _buff.erase(0, _header_size);

        if (_header->exist("content-length")) {
            Debug::checkpoint("\t{content-length} Extraction: [" + _header->getValue("content-length") + "]");
            _content_size = atoi(_header->getValue("content-length").c_str());
            return (process_length());
        } else if (_header->exist("transfer-encoding") && _header->getValue("transfer-encoding") == "chunked") {
            Debug::checkpoint("\t{transfer-encoding} : [" + _header->getValue("transfer-encoding") + "]");
            _chunked = true;
            return (process_chunked());
        }
        //Debug::checkpoint("\t{nothing to do}");
        return (true);
    }
    else if (_chunked)
        return (process_chunked());
    else if (_content_size > 0)
        return (process_length());
    else
        return (false);
}

bool Client::process_chunked() {
    size_t len = 0;
    std::string base("0123456789ABCDEF");
    //Debug::info("BUFF : [" + Debug::escapestr(_buff) + "]");
    
    if (_buff.length() == 0)
        return (false);

    size_t i = 0;
    while (i < _buff.length() && base.find(std::toupper(_buff.at(i))) != std::string::npos)
    {
        len = len * base.length() + base.find(std::toupper(_buff.at(i)));
        i++;
    }
    while (len + 4 <= _buff.length() - i)
    {
        _buff.erase(0, i + 2);
        if (len > 0)
            _content += _buff.substr(0, len);
        _buff.erase(0, len + 2);
        if (!len)
        {
            _buff.erase(0, _buff.length());
            return (true);
        }
        else
        {
            i = 0;
            len = 0;
            while (i < _buff.length() && base.find(std::toupper(_buff.at(i))) != std::string::npos)
            {
                len = len * base.length() + base.find(std::toupper(_buff.at(i)));
                i++;
            }
            if (i >= _buff.length())
                return (false);
        }
    }
    return (false);
}

bool Client::process_length() {
    _content += _buff;
    _content_size -= _buff.length();
    if (!_content_size)
        return (true);
    return (false);
}

bool Client::hasFinishedSending() { return !(getResponseLength()); }

Server *Client::getConf() { return (_conf); }
HttpHeader *Client::getHeader() { return (_header); }
std::string Client::getContent() { return (_content); }

void Client::process()
{
    Debug::checkpoint("Processing : ", _socket);
    //Debug::checkpoint("With data : [" + _content + "]");

    if (!Error::method_authorized(*_header, *_conf))
    {
        Debug::error("405 Unauthorized Method");
        _response = "HTTP/1.1 405 Method Not Allowed\r\n";

        if (_header->getMethod() != "HEAD")
        {
            std::string page;
            if (_conf->getErrorPage().find(405) != _conf->getErrorPage().end())
                page = Error::getErrorPageContent(405, *_conf);
            else
                page = DEFAULT_405_PAGE;
            char *tmp = ft_itoa(std::string(page).length());
            _response += "Content-Length:" + std::string(tmp) + "\r\n\r\n" + page;
            free(tmp);
        }
        else
            _response += "\r\n";
    }
    else if (!Error::file_exist(*_header, *_conf) && getType(_header->getMethod()) != POST && getType(_header->getMethod()) != PUT)
    {
        Debug::error("404 File Not Found");
        _response = "HTTP/1.1 404 File Not Found\r\n";

        if (_header->getMethod() != "HEAD")
        {
            std::string page;
            if (_conf->getErrorPage().find(404) != _conf->getErrorPage().end())
                page = Error::getErrorPageContent(404, *_conf);
            else
                page = DEFAULT_404_PAGE;
            char *tmp = ft_itoa(std::string(page).length());
            _response += "Content-Length:" + std::string(tmp) + "\r\n\r\n" + page;
            free(tmp);
        }
        else
            _response += "\r\n";
    }
    else if (getType(_header->getMethod()) == POST || getType(_header->getMethod()) == PUT)
    {
        std::string *path = Error::forceBuildPath(*_header, *_conf);
        std::map<std::string, Route>::reverse_iterator road = Error::getRoad(*_header, *_conf);

        if (road->second.getClientMaxBodySize() < _content.size())
        {
            _response = "HTTP/1.1 413 Request Entity Too Large\r\n\r\n";
        }
        else if (path != NULL && CGI()(*path, road->second))
        {
            CGI cgi;
            Debug::info("CGI PATH:" + *path);
            cgi.setFrom(*this, *path, &(road->second), _env);
            _response = cgi.process();
            std::string to_write = split(_response, "\r\n\r\n")[1];
            int fd = open(path->c_str(), O_CREAT | O_WRONLY, 0644);
            write(fd, to_write.c_str(), to_write.length());
            close(fd);
        }
        else
        {
            _response = "HTTP/1.1 200 OK\r\n\r\n"; // TODO RESPONSE ADD CONTENT
            if (path && isRegularFile(path->c_str()))
            {
                int fd = open(path->c_str(), O_CREAT | O_WRONLY, 0644);
                write(fd, _content.c_str(), _content.length());
                close(fd);
            }
        }
    }
    else
    {
        std::string *path = Error::file_exist(*_header, *_conf);
        std::map<std::string, Route>::reverse_iterator road = Error::getRoad(*_header, *_conf);
        if (CGI()(*path, road->second))
        {
            CGI cgi;

            cgi.setFrom(*this, *path, &(road->second), _env);
            _response = cgi.process();
        }
        else
            _response = "HTTP/1.1 200 OK\r\n\r\n";
    }
    Debug::checkpoint("Response : " + Debug::escapestr(_response.substr(0, 100000)));
    delete _header;
}

const char *Client::getResponse() { return (&(_response.c_str()[_from])); }
size_t Client::getResponseLength() { return (_response.length() - _from); }
void Client::substract(size_t len) { _from += len; }

Client::~Client() {}
