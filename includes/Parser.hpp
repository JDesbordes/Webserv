#ifndef PARSER_HPP
#define PARSER_HPP

#include "global.hpp"

class Server;

class Parser
{
    public:
        Parser();
        Parser(char *path);
        Parser &operator=(const Parser &);

        std::vector<Server> getConfig();

        ~Parser();
    private:
        Parser(const Parser &);

        std::string         _config_path;
        std::vector<Server> _result;
};

#endif // !PARSER_HPP