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

#define MAX_CONNECTIONS 5000
#define RECV_BUFFER_SIZE 1000000
#define MAX_URL 1000000

// #define ERR
// #define WARN
#define CP
// #define INFO

#define DEFAULT_200_PAGE "<h1>200 Success</h1>"
#define DEFAULT_201_PAGE "<h1>201 Created</h1>"
#define DEFAULT_204_PAGE "<h1>204 No Content</h1>"
#define DEFAULT_400_PAGE "<h1>400 Bad Request</h1>"
#define DEFAULT_401_PAGE "<h1>401 Unauthorized</h1>"
#define DEFAULT_403_PAGE "<h1>403 Forbidden</h1>"
#define DEFAULT_404_PAGE "<h1>404 Page not Found</h1>"
#define DEFAULT_405_PAGE "<h1>405 Method Not Allowed</h1>"
#define DEFAULT_413_PAGE "<h1>413 Pyload Too Large</h1>"
#define DEFAULT_500_PAGE "<h1>500 Internal Server Error</h1>"
#define DEFAULT_501_PAGE "<h1>501 Not Implemented</h1>"
#define DEFAULT_503_PAGE "<h1>503 Service Unavailable</h1>"
#define DEFAULT_504_PAGE "<h1>504 Gateway Time-out</h1>"

#define DEFAULT_200_MSG "HTTP/1.1 200 Success"
#define DEFAULT_201_MSG "HTTP/1.1 201 Created"
#define DEFAULT_204_MSG "HTTP/1.1 204 No Content"
#define DEFAULT_400_MSG "HTTP/1.1 400 Bad Request"
#define DEFAULT_401_MSG "HTTP/1.1 401 Unauthorized"
#define DEFAULT_403_MSG "HTTP/1.1 403 Forbidden"
#define DEFAULT_404_MSG "HTTP/1.1 404 Page not Found"
#define DEFAULT_405_MSG "HTTP/1.1 405 Method Not Allowed"
#define DEFAULT_413_MSG "HTTP/1.1 413 Payload Too Large"
#define DEFAULT_500_MSG "HTTP/1.1 500 Internal Server Error"
#define DEFAULT_501_MSG "HTTP/1.1 501 Not Implemented"
#define DEFAULT_503_MSG "HTTP/1.1 503 Service Unavailable"
#define DEFAULT_504_MSG "HTTP/1.1 504 Gateway Time-out"

#endif // !DEFINES_HPP