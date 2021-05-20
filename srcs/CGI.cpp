#include "CGI.hpp"

CGI::CGI() {}
CGI::CGI(const CGI &cgi) : _mapped_args(cgi._mapped_args), _content(cgi._content) {}
CGI &CGI::operator=(const CGI &cgi) {
    _mapped_args = cgi._mapped_args;
    _content = cgi._content;
    return (*this);
}

bool CGI::operator()(std::string path, Route &conf)
{
    path = split(path, "?")[0];
    std::vector<std::string> ext = split(path, ".");
    if (ext.size() > 1 && ext.back() == conf.getCGIExtension())
        return (true);
    return (false);
}

CGI::~CGI() {}

void CGI::setFrom(Client &c, std::string path, Route *conf, char **env)
{
    _errno = 200;
    Debug::checkpoint(path);

    std::stringstream ss;
    std::vector<std::string> tokens;

    char tmp_buf[2048];
    getcwd(tmp_buf, 2048);

    std::string complete_path = std::string(tmp_buf) + path.substr(1);

    _content = c.getContent();
    _road = conf;

    for (int i = 0; env[i]; i++)
    {
        std::string tmp(env[i]);
        _mapped_args.insert(std::pair<std::string, std::string>(tmp.substr(0, tmp.find("=")), tmp.substr(tmp.find("=") + 1)));
    }

    _mapped_args.insert(std::pair<std::string, std::string>("AUTH_TYPE", ""));
    ss.str("");
    ss << c.getContent().length();
    _mapped_args.insert(std::pair<std::string, std::string>("CONTENT_LENGTH", ss.str()));
    _mapped_args.insert(std::pair<std::string, std::string>("CONTENT_TYPE",
        c.getHeader()->getMethod() == "POST" && c.getHeader()->exist("Content-Type") ? c.getHeader()->getValue("Content-Type") : ""));
    
    _mapped_args.insert(std::pair<std::string, std::string>("GATEWAY_INTERFACE", "CGI/1.1"));

    tokens = split(path, ".");
    std::string path_info = "/" + (tokens[2].find("/") != std::string::npos ? tokens[2].substr(tokens[2].find("/") + 1) : "");

    Debug::error("Path info : " + path_info);

    _mapped_args.insert(std::pair<std::string, std::string>("PATH_INFO", c.getHeader()->getPath()));
    _mapped_args.insert(std::pair<std::string, std::string>("PATH_TRANSLATED", path_info));
    _mapped_args.insert(std::pair<std::string, std::string>("QUERY_STRING", path.find("?") != std::string::npos ? path.substr(path.find("?")) : ""));
    _mapped_args.insert(std::pair<std::string, std::string>("REMOTE_ADDR", "127.0.0.1"));
    _mapped_args.insert(std::pair<std::string, std::string>("REMOTE_IDENT", ""));
    _mapped_args.insert(std::pair<std::string, std::string>("REMOTE_USER", ""));
    _mapped_args.insert(std::pair<std::string, std::string>("REQUEST_METHOD", c.getHeader()->getMethod()));
    _mapped_args.insert(std::pair<std::string, std::string>("REQUEST_URI", c.getHeader()->getPath()));
    _mapped_args.insert(std::pair<std::string, std::string>("SCRIPT_NAME", path.find("?") != std::string::npos ? path.substr(0, path.find("?")) : path));

    _mapped_args.insert(std::pair<std::string, std::string>("SERVER_NAME", c.getConf()->getHost()));
    ss.str("");
    ss << c.getConf()->getPort();
    _mapped_args.insert(std::pair<std::string, std::string>("SERVER_PORT", ss.str()));
    _mapped_args.insert(std::pair<std::string, std::string>("SERVER_PROTOCOL", "HTTP/1.1"));
    
    _mapped_args.insert(std::pair<std::string, std::string>("SERVER_SOFTWARE", "Webserv/2.0"));

    std::map<const std::string, std::string> tmp_map = c.getHeader()->getItems();
    for (std::map<const std::string, std::string>::iterator itr = tmp_map.begin(); itr != tmp_map.end(); itr++)
    {
        std::string tmp = itr->first;
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
        _mapped_args.insert(std::pair<std::string, std::string>("HTTP_" + tmp, itr->second));
    }
}

char **CGI::getArgs()
{
    int i = 0;
    char **res;

    res = (char **)(malloc(sizeof(char *) * (_mapped_args.size() + 1)));
    for (std::map<std::string, std::string>::iterator itr = _mapped_args.begin(); itr != _mapped_args.end(); itr++)
    {
        res[i] = ft_strjoin(itr->first.c_str(), "="); 
        res[i] = ft_strfjoin(res[i], itr->second.c_str(), 1); 
        i++;
    }
    res[_mapped_args.size()] = NULL;
    return (res);
}

std::string CGI::process()
{
    pid_t		pid;
	int			saveStdin;
	int			saveStdout;
    char **args = getArgs();
    std::string res;

    for (int i = 0; args[i] != NULL; i++)
        Debug::info("[" + std::string(args[i]) + "]");
    Debug::checkpoint("Processing CGI ...");

	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();
	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	write(fdIn, _content.c_str(), _content.size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
		_errno = 500;
	else if (!pid)
	{
		char *const *nll = NULL;

		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(_road->getCGIPath().c_str(), nll, args);
		Debug::error("Execve crash [" + _road->getCGIPath() + "]: " + std::string(strerror(errno)));
		write(STDOUT_FILENO, "HTTP/1.1 500 Internal Server Error\r\n\r\n", ft_strlen("HTTP/1.1 500 Internal Server Error\r\n\r\n"));
	}
	else
	{
        //add select
		char	buffer[RECV_BUFFER_SIZE] = {0};
		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);
		ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, RECV_BUFFER_SIZE);
			ret = read(fdOut, buffer, RECV_BUFFER_SIZE - 1);
			res += buffer;
		}
	}

	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

    if (res == "HTTP/1.1 500 Internal Server Error\r\n\r\n")
    {
        _errno = 500;
        res = "\r\n\r\n";
        Debug::error("CGI 500 Error");
    }
    // res = parseResult(res);

    return (res);
}

std::string CGI::parseResult(std::string res)
{
    std::stringstream ss;
    std::stringstream output;
    std::vector<std::string> tokens = split(res, "\r\n\r\n"); 

    std::string tmp_header = tokens[0];
    std::string tmp_content = tokens[1];

    Debug::warning("Header: " + Debug::escapestr(tmp_header));

    tokens = split(tmp_header, "\r\n");
    
    std::vector<std::string> headers;
    for (std::vector<std::string>::iterator itr = tokens.begin(); itr != tokens.end(); itr++)
        if (itr->find("Status", 0, 6) != std::string::npos)
            _errno = ft_atoi(itr->substr(8).c_str());
        else
            headers.push_back(*itr);

    ss << "Content-Length:" << tmp_content.length();
    headers.push_back(ss.str());

    for (std::vector<std::string>::iterator itr = headers.begin(); itr != headers.end(); itr++)
    {
        Debug::warning("Token: [" + *itr + "]");
        output << *itr << "\r\n";
    }
    output << "\r\n";
    output << tmp_content;
    return (output.str());
}