#ifndef HTTP_ERROR_HPP
#define HTTP_ERROR_HPP

#include "global.hpp"

class HttpParser;

class HttpError {
    public:
        static std::string getPage(Server *, HttpParser *);
        static std::string getDefaultPage(int err);
        static std::string getStatusMsg(int err);

    private:
        HttpError();
        ~HttpError();
        HttpError &operator=(const HttpError &);
        HttpError(const HttpError &);
};

#endif // !HTTP_ERROR_HPP