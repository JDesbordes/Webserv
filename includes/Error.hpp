#ifndef ERROR_HPP
#define ERROR_HPP

#include "global.hpp"

class HttpHeader;

class Error {
    public:
        static std::string getErrorPageContent(int, Server&);
        static std::map<std::string, Route>::reverse_iterator getRoad(HttpHeader &header, Server &conf);
        static bool method_authorized(HttpHeader&, Server&);
        static std::string *file_exist(HttpHeader&, Server&);
        static std::string *forceBuildPath(HttpHeader &header, Server &conf);
        static std::vector<t_method_type> get_method_authorized(HttpHeader &header, Server &conf);
        class RoadNotFoundException : public std::exception { virtual const char* what() const throw(); };

        ~Error();

    private:
        Error();
        Error(const Error &);
        Error &operator=(const Error &);
};

#endif