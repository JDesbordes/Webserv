#include "utils.hpp"

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(" \n\r\t\f\v");
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(" \n\r\t\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

std::vector<std::string> split_parser(std::string str, std::string delimiter)
{
    std::vector<std::string> elements;
    
    for (size_t i = 0; i < str.size(); i++)
        for (size_t j = 1; j < delimiter.size(); j++)
            if (str[i] == delimiter[j])
                str[i] = delimiter[0];
    size_t pos = 0;
    std::string token;
    std::string c(1, delimiter[0]);
    while ((pos = str.find(c)) != std::string::npos)
    {
        token = str.substr(0, pos);
        elements.push_back(token);
        str.erase(0, pos + 1);
    }
    elements.push_back(str.substr(0, str.length()));
    return (elements);
}

void parse_error(std::string err, std::string supply)
{
    std::cout << "\033[1;91mParsing error (" << err << ") " << supply << "\033[0m" << std::endl;
    exit(1);
}

int noblock(int fd)
{
    return (fcntl(fd, F_SETFL, O_NONBLOCK));
}

std::vector<std::string> split(std::string s, std::string delimiter) 
{
    std::vector<std::string> elements;
    
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        elements.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    elements.push_back(s.substr(0, s.length()));
    
    return (elements);
}

void lower(std::string &s) {
    for (size_t i = 0; i != s.length(); i++)
        s[i] = std::tolower(s[i]);
}

t_method_type getType(std::string type)
{
	if (type == "GET") return (GET);
	else if (type == "HEAD") return (HEAD);
	else if (type == "POST") return (POST);
	else if (type == "PUT") return (PUT);
	else if (type == "DELETE") return (DELETE);
	else if (type == "CONNECT") return (CONNECT);
	else if (type == "OPTIONS") return (OPTIONS);
	else if (type == "TRACE") return (TRACE);
	else if (type == "PATCH") return (PATCH);
	else return (ERROR);
}

std::string getStringType(t_method_type type)
{
	if (type == GET) return ("GET");
	else if (type == HEAD) return ("HEAD");
	else if (type == POST) return ("POST");
	else if (type == PUT) return ("PUT");
	else if (type == DELETE) return ("DELETE");
	else if (type == CONNECT) return ("CONNECT");
	else if (type == OPTIONS) return ("OPTIONS");
	else if (type == TRACE) return ("TRACE");
	else if (type == PATCH) return ("PATCH");
	else return ("ERROR");
}

int isRegularFile(const char *path)
{
    struct stat path_stat;
    path_stat.st_mode = 0;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDirectory(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) < 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
