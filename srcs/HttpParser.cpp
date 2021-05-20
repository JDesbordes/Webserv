#include "HttpParser.hpp"

HttpParser::HttpParser() : _errno(0) {}

HttpParser::HttpParser(const HttpParser &o)
{
    _errno = o._errno;
    _method = o._method;
    _content = o._content;
    _path = o._path;
    _http_version = o._http_version;
    _headers = o._headers;
    _initial_path = o._initial_path;
    _road = o._road;
}

HttpParser &HttpParser::operator=(const HttpParser &o)
{
    if (this == &o)
        return (*this);
    this->~HttpParser();
    return *new (this) HttpParser(o);
}

std::string HttpParser::processParse(Client &client, Server *serv, std::string raw_header, std::string content, char **env)
{
    raw_header = raw_header.substr(0, raw_header.find("\r\n\r\n"));
    std::vector<std::string> tokens = split(raw_header, "\r\n");
    _content = content;
    _env = env;

    while (tokens.size() > 1 && isValid())
    {
        if (tokens.back().find(":") == std::string::npos)
            _errno = 400;
        else
            _headers.insert(std::pair<std::string, std::string>(tokens.back().substr(0, tokens.back().find(":")), tokens.back().substr(tokens.back().find(":") + 1)));
        tokens.pop_back();
    }
    tokens = split(tokens[0], " ");
    if (tokens.size() != 3 || getType(tokens[0]) == ERROR)
        _errno = 400;
    else
    {
        _method = getType(tokens[0]);
        _path = tokens[1];
        _initial_path = tokens[1];
        _http_version = tokens[2];
    }

    if (_errno) { // SI ERREUR AVANT PROCESS PAGE
        _header += HttpError::getStatusMsg(_errno) + "\r\n";
        _page = HttpError::getPage(serv, this);
    } else { // PROCESS
        Debug::error("Request path: " + _initial_path);
        processPath(client, serv);
        if (_errno) {// SI ERREUR PDT PROCESS
            Debug::error("Error while processing", _errno);
            _header = HttpError::getStatusMsg(_errno) + "\r\n" + _header;
            _page = HttpError::getPage(serv, this);
        } else {// SINON RECUPERE JUSTE LE STATUS
            Debug::checkpoint("No error while processing", _status);
            _header = HttpError::getStatusMsg(_status) + "\r\n" + _header;
        }
    }
    
    Debug::warning("Header : " + Debug::escapestr(_header));
    if (_method == HEAD)
        return (_header + "\r\n");
    if (_header.find("Content-Length") != std::string::npos) {
        std::stringstream ss;
        ss << "Content-Length: " << _page.length() << "\r\n";
        _header += ss.str();
    }
    return (_header + "\r\n" + _page);
}

void HttpParser::processPath(Client &c, Server *serv)
{
    std::string res;

    if (URLAliased(serv))
        _path = modifiedURL(serv);
    else
        _road = NULL;
    _path = resolvePath();
    if (!isFile())
        appendIndex();

    Debug::info("Final path : [" + _path + "]");
    if (_road != NULL && _content.length() > _road->getClientMaxBodySize())
    {
        _errno = 413;
        _header += "Connection: close\r\n";
        return;
    }

    if (!methodAllowed())
    {
        std::stringstream ss;
        ss << "Allow: ";
        if (_road != NULL)
            for (std::vector<t_method_type>::iterator itr = _road->getMethod().begin(); itr != _road->getMethod().end(); itr++)
                ss << getStringType(*itr) << ", ";
        _header += ss.str().substr(0, ss.str().length() - 2) + "\r\n";
        _errno = 405;
    }
    else if (_road->getAuthBasicUserFile() != "")
    {
        if (_headers.find("Authorization") == _headers.end())
        {
            _header += "WWW-Authenticate: Basic realm=\"" + _road->getAuthBasic() + "\", charset=UTF-8\r\n";
            _header += Date()();
            _errno = 401;
        }
        else
        {
            std::string encoded = split(_headers.find("Authorization")->second, " ")[2];
            std::string decoded;
            Debug::error(encoded);
            Debug::error(Base64::Decode(encoded, decoded));
            Debug::error("Debug:[" + decoded + "]");
            std::vector<std::string> tkns = split(decoded, ":");
            if (_road->getAuthBasicUserFileList().find(tkns[0]) != _road->getAuthBasicUserFileList().end() &&
                _road->getAuthBasicUserFileList().find(tkns[0])->second == tkns[1])
                redirectMethod(c);
            else
            {
                _header += Date()();
                _errno = 403;
            }
        }
    } else
        redirectMethod(c);
}

void HttpParser::redirectMethod(Client &c)
{
    if (_method == GET || _method == HEAD)
        getMethod(c);
    else if (_method == POST)
        postMethod(c);
    else if (_method == PUT)
        putMethod();
}

void HttpParser::getMethod(Client &c)
{
    if (CGI()(_path, *_road))
        execCgi(c);
    else if (isFile())
    {
        std::string str;
        std::ifstream ifile(_path);

        if (!ifile.is_open())
            _errno = 500;
        else {
            while (getline(ifile, str))
                _page += str;
            _status = 200;
            ifile.close();
        }
    }
    else if (_road->getAutoIndex())
        autoIndex();
    else
        _errno = 404;
}

void HttpParser::postMethod(Client &c)
{
    if (CGI()(_path, *_road))
        execCgi(c);
    else
        _status = 204;
}

void HttpParser::putMethod()
{
    std::ofstream ofile;

    if (isFile())
    {
        ofile.open(_path);
		ofile << _content;
		ofile.close();
        _status = 204;
    }
    else
    {
        ofile.open(_path, std::ofstream::out | std::ofstream::trunc);
        if (!ofile.is_open())
        {
            _errno = 403;
        }
        else
        {
            ofile << _content;
            ofile.close();
            _status = 201;
        }
    }
}

void HttpParser::autoIndex()
{
    _page = "<h1>" + _initial_path + "/</h1>";
    struct dirent *current;
    DIR *directory = opendir(_path.c_str());
    if (!directory)
        _errno = 404;
    else
    {
        _page += "<table><tbody><tr><th>Name</th><th>Size (TODO)</th></tr><tr><th colspan=\"5\"><hr></th></tr>";
        while ((current = readdir(directory)))
        {
            if (std::string(current->d_name) == ".")
                ;
            else if (std::string(current->d_name) == "..")
                _page += "<tr><td align=\"left\"><a href=\"..\">Parent Directory</a></td><td align=\"center\">-</td></tr>";
            else
                _page += "<tr><td align=\"left\"><a href=\"" + std::string(current->d_name) + "\">" + std::string(current->d_name) + "</a></td><td align=\"center\">0</td></tr>";
        }
        _page += "</tbody></table>";
        _status = 200;
    }
    closedir(directory);
}

void    HttpParser::execCgi(Client &c)
{
    CGI cgi;

    cgi.setFrom(c, _path, _road, _env);
    std::string tmp_cgi = cgi.process();
    _header = tmp_cgi.substr(0, tmp_cgi.find("\r\n\r\n"));
    _header += "\r\n";
    _page = tmp_cgi.substr(tmp_cgi.find("\r\n\r\n") + 4);
    if (cgi._errno / 100 == 2)
        _status = cgi._errno;
    else
        _errno = cgi._errno;
}

bool HttpParser::methodAllowed()
{
    for (std::vector<t_method_type>::iterator itr = _road->getMethod().begin(); itr != _road->getMethod().end(); itr++)
        if (_method == *itr)
            return (true);
    return (false);
}

bool HttpParser::URLAliased(Server *serv)
{
    for (std::map<std::string, Route>::reverse_iterator itr = serv->getRoute().rbegin(); itr != serv->getRoute().rend(); itr++)
    {
        if (_path.find(itr->first, 0) != std::string::npos)
        {
            _road = &(itr->second);
            return (true);
        }
    }
    return (false);
}

std::string HttpParser::modifiedURL(Server *serv)
{
    for (std::map<std::string, Route>::reverse_iterator itr = serv->getRoute().rbegin(); itr != serv->getRoute().rend(); itr++)
        if (_path.find(itr->first, 0) != std::string::npos)
            return (_path.replace(0, itr->first.length() + 1, itr->second.getRoot()));
    return (_path);
}

std::string HttpParser::resolvePath()
{
    char buff[PATH_MAX];

    getcwd(buff, PATH_MAX);
    _path = std::string(buff) + _path.substr(1);
    return (_path);
}

bool HttpParser::isFile()
{
    struct stat s;
    if (!stat(_path.c_str(), &s) && s.st_mode & S_IFREG)
        return (true);
    return (false);
}

std::string HttpParser::appendIndex()
{
    if (!_road)
        return (_path);
    else if (_road->getIndex().size() > 0 && _method != POST)
    {
        if (_path.at(_path.length() - 1) == '/')
            _path += _road->getIndex()[0];
        else
            _path += "/" + _road->getIndex()[0];
    }
    return (_path);
}

void HttpParser::debugHeaders()
{
    for (std::map<std::string, std::string>::iterator itr = _headers.begin(); itr != _headers.end(); itr++)
        Debug::warning("[" + itr->first + "] = [" + itr->second + "]");
}

int HttpParser::getErrno() { return (_errno); }
bool HttpParser::isValid() { return (!_errno); }

HttpParser::~HttpParser() {}