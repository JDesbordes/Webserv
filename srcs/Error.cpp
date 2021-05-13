#include "Error.hpp"

std::string Error::getErrorPageContent(int err, Server &conf)
{
    std::string res = "";
    std::string path = conf.getErrorPage().find(err)->second;
    int fd = open(path.c_str(), O_RDONLY);
    char *line;
    int r;

    while ((r = get_next_line(fd, &line)) > 0)
    {
        res += line;
        free(line);
    }
    if (!r)
    {
        res += line;
        free(line);
    }
    else
    {
        Debug::error("Error page [" + path + "] cannot be loaded !");
        res = "Error page cannot be loaded, please contact an admin";
    }
    return (res);
}

std::map<std::string, Route>::reverse_iterator Error::getRoad(HttpHeader &header, Server &conf)
{
    std::string path = header.getPath();

    if (path.at(path.length() - 1) == '/')
        path = path.substr(0, path.length() - 1);
    for (std::map<std::string, Route>::reverse_iterator itr = conf.getRoute().rbegin(); itr != conf.getRoute().rend(); itr++)
    {
        std::string tmp = itr->first;
        if (tmp != "" && tmp.at(tmp.length() - 1) == '/')
            tmp = tmp.substr(0, tmp.length() - 1);
        if (path.find(tmp) != std::string::npos || tmp == "")
            return (itr);
    }
    throw Error::RoadNotFoundException();
}

bool Error::method_authorized(HttpHeader &header, Server &conf)
{
    std::string tmp_path = header.getPath();

    try {
        Route &road = getRoad(header, conf)->second;
        for (std::vector<t_method_type>::iterator itr2 = road.getMethod().begin(); itr2 != road.getMethod().end(); itr2++)
        {
            Debug::warning("Output : " + tmp_path + " Checked : " + getStringType(getType(header.getMethod())) + " | " + getStringType(*itr2));            
            if (getType(header.getMethod()) == *itr2)
                return (true);
        }
    } catch (Error::RoadNotFoundException &e) {}
    return (false);
}

std::vector<t_method_type> Error::get_method_authorized(HttpHeader &header, Server &conf)
{
    std::string tmp_path = header.getPath();
    std::vector<t_method_type> res;

    try {
        Route &road = getRoad(header, conf)->second;
        return (road.getMethod()); 
    } catch (Error::RoadNotFoundException &e) {}
    return (res);
}

std::string *Error::file_exist(HttpHeader &header, Server &conf)
{
    int r;
    char buff[2];
    struct stat buf;
    std::string *path = new std::string("");
    *path = header.getPath();

    try {
        std::map<std::string, Route>::reverse_iterator road = getRoad(header, conf);
        if (road->first.length() == path->length())
            *path += "/";
        path->replace(0, road->first.length(), road->second.getRoot());

        int a = isRegularFile(path->c_str());
        if (a)
        {
            Debug::info("C0");
            int fd = open(path->c_str(), O_RDONLY);
            if (fd == -1)
            {
                Debug::info("C1");
                return (NULL);
            }
            r = read(fd, buff, 0);
            if (r == -1)
            {
                Debug::info("C2");
                return (NULL);
            }
            Debug::checkpoint("Path Found [" + *path + "]");
            return (path);
        }

        if (isDirectory(path->c_str()))
            for (size_t i = 0; i < road->second.getIndex().size(); i++)
            {
                Debug::warning("Try path :" + *path + "/" + road->second.getIndex()[i]);
                if (stat(std::string(*path + "/" + road->second.getIndex()[i]).c_str(), &buf) >= 0)
                {
                    Debug::info("A0");
                    int fd = open(std::string(*path + "/" + road->second.getIndex()[i]).c_str(), O_RDONLY);
                    if (fd == -1)
                    {
                        Debug::info("A1");
                        continue;
                    }
                    r = read(fd, buff, 0);
                    if (r == -1)
                    {
                        Debug::info("A2");
                        continue;
                    }
                    *path = *path + "/" + road->second.getIndex()[i];
                    Debug::checkpoint("Path Found [" + *path + "]");
                    return (path);
                }
                Debug::error(strerror(errno));
            }   
        if (road->second.getIndex().size() > 0)
            return (NULL);
        else if (road->second.getAutoIndex() == 1 && isDirectory(path->c_str()))
        {
            Debug::warning("TODO Auto Index");
            return (path);
        }
    } catch (Error::RoadNotFoundException &e) {}
    return (NULL);
}

std::string *Error::forceBuildPath(HttpHeader &header, Server &conf)
{
    std::string *path = new std::string();
    *path = header.getPath();

    try {
        Debug::warning("E0");
        std::map<std::string, Route>::reverse_iterator road = getRoad(header, conf);
        Debug::warning("E1");
        if (road->first.length() == path->length())
            *path += "/";
        Debug::warning("E2");
        path->replace(0, road->first.length(), road->second.getRoot());
        Debug::warning("E3");
        Debug::error("Path: " + *path + " size:", road->second.getIndex().size());
        if (isDirectory(path->c_str()))
        {
            Debug::warning("E4");
            if (road->second.getIndex().size() > 0)
                *path += "/" + road->second.getIndex()[0];
            Debug::warning("E5");
            return (path);
        }
    } catch (Error::RoadNotFoundException &e) {}
    Debug::warning("E6");
    return (path);
}

const char *Error::RoadNotFoundException::what() const throw() { return ("Error: Road not found"); }

Error::~Error() {}
