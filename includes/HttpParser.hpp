#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include "global.hpp"

class Client;

class HttpParser {
    public:
        HttpParser();
        HttpParser(const HttpParser &);
        HttpParser &operator=(const HttpParser &);
        ~HttpParser();

        std::string processParse(Client &client, Server *serv, std::string raw_header, std::string content, char **env);
        void processPath(Client &client, Server *serv);
        
        void    redirectMethod(Client &c);
        void    getMethod(Client &c);
        void    postMethod(Client &c);
        void    putMethod();
        void    autoIndex();
        void    execCgi(Client &c);

        bool methodAllowed();

        bool URLAliased(Server *serv);
        std::string modifiedURL(Server *serv);
        std::string resolvePath();
        bool isFile();
        std::string appendIndex();

        void debugHeaders();

        int getErrno();
        bool isValid();

    private:

        int _errno;
        int _status;
        std::map<std::string, std::string> _headers;
        std::string _content;
        t_method_type _method;
        std::string _path;
        std::string _initial_path;
        std::string _http_version;
        Route *_road;
        char **_env;

        std::string _header;
        std::string _page;
};

#endif
