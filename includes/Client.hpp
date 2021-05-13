#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "global.hpp"

class HttpHeader;
class CGI;

class Client
{
    public:
        Client();
        Client(SOCKET, char **, Server*);
        Client(const Client &);
        Client &operator=(const Client &);
        
        void append(std::string data);
        bool hasFinishedReading();
        bool hasFinishedSending();
        void process();
        bool process_chunked();
        bool process_length();

        Server *getConf();
        HttpHeader *getHeader();
        std::string getContent();
        const char *getResponse();
        size_t getResponseLength();
        void substract(size_t len);

        ~Client();
    private:
        SOCKET _socket;
	    char **_env;
        Server *_conf;
        std::string _buff;
        size_t _from;

        HttpHeader *_header;
        bool _header_end;
        size_t _header_size;

        std::string _content;
        bool _content_end;
        size_t _content_size;
        bool _chunked;

        std::string _response_content;
        std::vector<std::string> _response_header;
        std::string _response;
        bool _all_receive;
};

#endif