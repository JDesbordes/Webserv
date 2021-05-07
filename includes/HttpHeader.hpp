#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include "global.hpp"

class HttpHeader {
    public:
        HttpHeader();
        HttpHeader(const HttpHeader &);
        HttpHeader(std::string);
        const HttpHeader &operator=(const HttpHeader &);

        std::pair<std::string, std::string> get(std::string);
        std::string getKey(std::string);
        std::string getValue(std::string);
        std::map<const std::string, std::string> getItems();

        std::string getPath();
        std::string getMethod();

        bool exist(std::string);

        ~HttpHeader();
    private:
        std::map<const std::string, std::string> _headers;
        std::string _method;
        std::string _path;
};

#endif
