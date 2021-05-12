#ifndef DEFINES_HPP
#define DEFINES_HPP

#include "global.hpp"

#define RST "\e[0m"
#define RED "\e[1;31m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"
#define DGR "\e[1;90m"

#define FD_ERROR -1
#define FD_ERROR_MSG "Config path error"
#define TOKEN_ERROR_MSG "Config parsing error"

typedef int SOCKET;

#define MAX_CONNECTIONS 4096
#define RECV_BUFFER_SIZE 1000000
#define MAX_URL 1000000
#define WORKERS 5

#define DEFAULT_200_PAGE "<h1>200 Success/h1>"
#define DEFAULT_301_PAGE "<h1>301 Redirection permanante</h1>"
#define DEFAULT_302_PAGE "<h1>302 Redirection temporaire</h1>"
#define DEFAULT_401_PAGE "<h1>401 Unauthorized</h1>"
#define DEFAULT_403_PAGE "<h1>403 Forbidden</h1>"
#define DEFAULT_404_PAGE "<h1>404 Page not Found</h1>"
#define DEFAULT_405_PAGE "<h1>405 Method Not Allowed</h1>"
#define DEFAULT_500_PAGE "<h1>500 Internal Server Error</h1>"
#define DEFAULT_503_PAGE "<h1>503 Service Unavailable</h1>"
#define DEFAULT_504_PAGE "<h1>504 Gateway Time-out</h1>"

#endif // !DEFINES_HPP