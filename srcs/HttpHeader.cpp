#include "HttpHeader.hpp"

HttpHeader::HttpHeader() {}
HttpHeader::HttpHeader(const HttpHeader &o) : _headers(o._headers) {}
HttpHeader::HttpHeader(std::string raw_data) {
    std::vector<std::string> tokens = split(raw_data, "\r\n");

    for (std::vector<std::string>::iterator itr = tokens.begin(); itr != tokens.end(); itr++)
    {
        std::string key, value;
        size_t sep = itr->find(':');
        if (sep != std::string::npos)
        {
            key = trim(itr->substr(0, sep));
            lower(key);
            value = ltrim(itr->substr(sep + 1));
            _headers.insert(std::pair<std::string, std::string>(key, value));
            Debug::info("Add key : [" + key + "] value : [" + value + "]");
        }
        else if (*itr != "")
        {
            _method = itr->substr(0, itr->find(' '));
            _path = itr->substr(itr->find(' ') + 1, itr->find(' ', itr->find(' ') + 1) - (itr->find(' ') + 1));
            Debug::info("Add method : [" + _method + "] path : [" + _path + "]");
        }
    }
} 
const HttpHeader &HttpHeader::operator=(const HttpHeader &o) {
    _headers = o._headers;
    return (*this);
}

std::pair<std::string, std::string> HttpHeader::get(std::string key) {
    lower(key);
    std::map<const std::string, std::string>::iterator itr = _headers.find(key);
    if (itr != _headers.end())
        return (*itr);
    else
        return (std::pair<std::string, std::string>("", ""));
}

std::string HttpHeader::getKey(std::string key) {
    lower(key);
    return get(key).first;
}

std::string HttpHeader::getValue(std::string key) {
    lower(key);
    return get(key).second;
}

std::map<const std::string, std::string> HttpHeader::getItems() {
    return (_headers);
}

std::string HttpHeader::getPath() { return (_path); }
std::string HttpHeader::getMethod() { return (_method); }

bool HttpHeader::exist(std::string key) {
    lower(key);
    return (_headers.find(key) != _headers.end());
}

HttpHeader::~HttpHeader() {}
