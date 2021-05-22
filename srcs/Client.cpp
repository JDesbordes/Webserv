#include "Client.hpp"

Client::Client() {}
Client::Client(SOCKET socket, char **env, Server *conf) : _socket(socket), _env(env), _conf(conf), _buff(""),
    _from(0), _header(NULL), _header_end(false), _header_size(0), _content(""), _content_end(false), _content_size(0), _chunked(false), _all_receive(false) {}
Client::Client(const Client &o) : _socket(o._socket), _env(o._env), _conf(o._conf), _buff(o._buff),
    _from(0), _header(NULL), _header_end(false), _header_size(0), _content(""), _content_end(false), _content_size(0), _chunked(false), _all_receive(false) {}
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
    _all_receive = o._all_receive;
    return (*this);
}

void Client::append(std::string data) {
    if (data.length() > 0)
        time(&last_action);
    _buff += data; 
    // Debug::info("buff size: ", _buff.length());
    // Debug::info("content size: ", _content.length());
}

bool Client::hasFinishedReading() {
    //Debug::info("Start _buff state [" + Debug::escapestr(_buff) + "]");
    if (_all_receive)
        return (_all_receive);
    else if (!_chunked && !_content_size && _buff.find("\r\n\r\n") != std::string::npos)
    {
        _header_end = true;
        _header_size = _buff.find("\r\n\r\n") + 4;
        _raw_header = _buff.substr(0, _header_size);
        _header = new HttpHeader(_buff.substr(0, _header_size));

        _buff.erase(0, _header_size);

        if (_header->exist("content-length")) {
            Debug::checkpoint("\t{content-length} Extraction: [" + _header->getValue("content-length") + "]");
            _content_size = atoi(_header->getValue("content-length").c_str());
            _all_receive = process_length();
        } else if (_header->exist("transfer-encoding") && _header->getValue("transfer-encoding") == "chunked") {
            Debug::checkpoint("\t{transfer-encoding} : [" + _header->getValue("transfer-encoding") + "]");
            _chunked = true;
            _all_receive = process_chunked();
        } else {
            Debug::checkpoint("\t{nothing to do}");
            _all_receive = true;
        }
    }
    else if (_chunked)
        _all_receive = process_chunked();
    else if (_content_size > 0)
        _all_receive = process_length();
    return (_all_receive);
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
    HttpParser httpParser = HttpParser();
    std::string page = httpParser.processParse(*this, _conf, _raw_header, _content, _env);
    //Debug::error("PAGE RESULT: " + page.substr(0, 2000));
    _response = page;
    return ;
}

const char *Client::getResponse() { return (&(_response.c_str()[_from])); }
size_t Client::getResponseLength() 
{
    // Debug::checkpoint("response length = ", _response.length());
    // Debug::checkpoint("response length sent = ", _from);
    return (_response.length() - _from); 
}
void Client::substract(size_t len) {
    if (len > 0)
        time(&last_action);
    _from += len;
    }

Client::~Client() {}
