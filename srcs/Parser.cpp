#include "Parser.hpp"

Parser::Parser() {}

Parser &Parser::operator=(const Parser &o)
{
    _config_path = o._config_path;
    _result = o._result;
    return (*this);
}

Parser::Parser(char *path)
{
    char buffer[1];
    std::string config_content;
    int config_fd;
    
    // ? Open Config File
    config_fd = open(path, O_RDONLY);
    if (config_fd == FD_ERROR)
        parse_error(FD_ERROR_MSG, "");

    // ? Read Config Content
    while (read(config_fd, &buffer, 1) > 0)
        config_content += buffer[0];
    
    // ? Ignore comment
    std::string clear_comments = "";
    for (size_t i = 0; i < config_content.size(); i++)
    {
        if (config_content[i] == '#')
            while (config_content[i] != '\n' && i < config_content.size())
                i++;
        clear_comments += config_content[i];
    }

    int level = 0;
    for (size_t i = 0; i < clear_comments.size(); i++)
        if (clear_comments[i] == '{')
            level++;
        else if (clear_comments[i] == '}')
            level--;
    if (level != 0)
        parse_error("Bracket Error", "bad bracket detected");

    // ? split_parser into sections
    std::vector<std::string> split_parserted = split_parser(clear_comments, "{}");

    for (size_t i = 0; i < split_parserted.size(); i++)
        split_parserted[i] = trim(split_parserted[i]);

    // ? Check if first is server
    size_t i = 0;
    if (split_parserted[i].compare(0, 7, "server"))
        parse_error("Bracket Error", "at first block");

    // ? Check for body
    while (++i < split_parserted.size() - 2)
        if ((split_parserted[i] == "" && split_parserted[i + 1].compare(0, 7, "server")) || (split_parserted[i] != "" && !split_parserted[i + 1].compare(0, 7, "server")))
            parse_error("Bracket Error", "");
    // ? Check for last
    if (split_parserted.back() != "" || split_parserted[split_parserted.size() - 2] != "")
        parse_error("Bracket Error", "at last block");

    // ? Here file bracket is ok, select line by line
    std::vector<std::string> lines;
    for (size_t j = 0; j < split_parserted.size(); j++)
    {
        std::vector<std::string> tmp = split_parser(split_parserted[j], "\n");
        for (size_t k = 0; k < tmp.size(); k++)
        {
            tmp[k] = trim(tmp[k]);
            if (tmp[k] != "")
                lines.push_back(tmp[k]);
        }
    }

    int last_type = 0;
    std::map<std::string, Route>::iterator last_location;
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (!lines[i].compare(0, 7, "server") && (last_type = 1)) // ? Si c'est un nouveau server, on le creer
            _result.push_back(Server());
        else
        {
            // ? Sinon on split_parser les k, v
            std::vector<std::string> split_parserted_line = split_parser(lines[i], " \n\r\t\f\v");
            std::vector<std::string> cleaned;

            // ? clean ""
            for (std::vector<std::string>::iterator itr = split_parserted_line.begin(); itr != split_parserted_line.end(); itr++)
                if (*itr != "")
                    cleaned.push_back(*itr);

            // ? check format
            if (cleaned[0] == "location" && (last_type = 2))
            {
                if (cleaned.size() != 2)
                    parse_error("Location Error", "too many args");
                if (cleaned.back()[cleaned.back().length() - 1] == '/')
                    cleaned.back() = cleaned.back().substr(0, cleaned.back().length() - 1);
                last_location = _result.back().addRoute(cleaned.back(), Route());
                continue;
            }
            else if (lines[i][lines[i].length() - 1] != ';')
                parse_error("Semicolon Error", "semicolon is missing at the end of the line.");

            // ? remove semicolon
            cleaned[cleaned.size() - 1] = cleaned[cleaned.size() - 1].substr(0, cleaned[cleaned.size() - 1].length() - 1);
            
            // ? check key
            if (last_type == 1 && cleaned[0] == "listen" && cleaned.size() == 2)
            {
                if (split_parser(cleaned[1], ":")[0] == "localhost")
                    _result.back().setHost("127.0.0.1");
                else
                    _result.back().setHost(split_parser(cleaned[1], ":")[0]);
                _result.back().setPort(ft_atoi(split_parser(cleaned[1], ":")[1].c_str()));
            }
            else if (last_type == 1 && cleaned[0] == "server_name" && cleaned.size() == 2)
            {
                _result.back().setServerName(cleaned[1]);
            }
            else if (last_type == 1 && cleaned[0] == "error_page" && cleaned.size() >= 2)
            {
                for (size_t j = 1; j < cleaned.size() - 1; j++)
                    _result.back().addErrorPage(ft_atoi(cleaned[j].c_str()), cleaned.back());
            }
            else if (last_type == 2 && cleaned[0] == "client_max_body_size" && cleaned.size() == 2)
            {
                if (cleaned[1][cleaned[1].length() - 1] == 'G')
                {
                    cleaned[1] = cleaned[1].substr(0, cleaned[1].length() - 1);
                    cleaned[1] += "000000000";
                }
                else if (cleaned[1][cleaned[1].length() - 1] == 'M')
                {
                    cleaned[1] = cleaned[1].substr(0, cleaned[1].length() - 1);
                    cleaned[1] += "000000";
                }
                else if (cleaned[1][cleaned[1].length() - 1] == 'K')
                {
                    cleaned[1] = cleaned[1].substr(0, cleaned[1].length() - 1);
                    cleaned[1] += "000";
                }
                last_location->second.setClientMaxBodySize(ft_atoi(cleaned[1].c_str()));
            }
            else if (last_type == 2 && cleaned[0] == "method" && cleaned.size() >= 2)
            {
                for (size_t j = 1; j < cleaned.size(); j++)
                    if (cleaned[j] == "GET") last_location->second.addMethod(GET);
                    else if (cleaned[j] == "HEAD") last_location->second.addMethod(HEAD);
                    else if (cleaned[j] == "POST") last_location->second.addMethod(POST);
                    else if (cleaned[j] == "PUT") last_location->second.addMethod(PUT);
                    else if (cleaned[j] == "DELETE") last_location->second.addMethod(DELETE);
                    else if (cleaned[j] == "CONNECT") last_location->second.addMethod(CONNECT);
                    else if (cleaned[j] == "OPTIONS") last_location->second.addMethod(OPTIONS);
                    else if (cleaned[j] == "TRACE") last_location->second.addMethod(TRACE);
                    else if (cleaned[j] == "PATCH") last_location->second.addMethod(PATCH);
                    else parse_error("Field Error", "method " + cleaned[j] + " unrecognized");
            }
            else if (last_type == 2 && cleaned[0] == "root" && cleaned.size() == 2)
            {
                if (cleaned.back()[cleaned.back().length() - 1] == '/')
                    cleaned.back() = cleaned.back().substr(0, cleaned.back().length() - 1);
                last_location->second.setRoot(std::string(cleaned[1]));
            }
            else if (last_type == 2 && cleaned[0] == "autoindex" && cleaned.size() == 2)
            {
                if (cleaned[1] == "on") last_location->second.setAutoIndex(1);
                else if (cleaned[1] == "off") last_location->second.setAutoIndex(0);
                else parse_error("Field Error", "autoindex bad value");
            }
            else if (last_type == 2 && cleaned[0] == "index" && cleaned.size() >= 2)
            {
                for (size_t j = 1; j < cleaned.size(); j++)
                    last_location->second.addIndex(cleaned[j]);
            }
            else if (last_type == 2 && cleaned[0] == "cgi_extension" && cleaned.size() == 2)
            {
                last_location->second.setCGIExtension(cleaned[1]);
            }
            else if (last_type == 2 && cleaned[0] == "cgi_path" && cleaned.size() == 2)
            {
                last_location->second.setCGIPath(cleaned[1]);
            }
            else parse_error("Unrecognized key Error", cleaned[0]);
        }
    }
    close(config_fd);
}

std::vector<Server> Parser::getConfig() { return (_result); }

Parser::~Parser() {}