#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <map>
#include <set>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sstream>
#include <pthread.h>
#include "libft.hpp"
#include "defines.hpp"
#include "typedefs.hpp"
#include "utils.hpp"

// static int pid[WORKERS];
void int_handler(int);
static SOCKET server_socket;

#ifdef DEBUG_HPP
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN bool d;

#include "Date.hpp"
#include "Base64.hpp"

#include "Debug.hpp"
#include "Route.hpp"
#include "Server.hpp"

#include "Parser.hpp"
#include "HttpHeader.hpp"
#include "HttpParser.hpp"
#include "Error.hpp"
#include "HttpError.hpp"
#include "Client.hpp"
#include "CGI.hpp"

#endif // !GLOBAL_HPP
