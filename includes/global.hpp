#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <exception>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sstream>
#include "libft.hpp"
#include "defines.hpp"
#include "typedefs.hpp"
#include "utils.hpp"

void int_handler(int);
static SOCKET server_socket;

#include "Debug.hpp"
#include "Route.hpp"
#include "Server.hpp"
#include "Parser.hpp"
#include "HttpHeader.hpp"
#include "Error.hpp"
#include "Client.hpp"
#include "CGI.hpp"

#endif // !GLOBAL_HPP