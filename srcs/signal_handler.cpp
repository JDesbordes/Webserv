#include "global.hpp"

void int_handler(int)
{
    close(server_socket);
    std::cout << "\033[1;31m\n\n\tServer stopped\033[0;0m" << std::endl;
    exit(EXIT_SUCCESS);
}
