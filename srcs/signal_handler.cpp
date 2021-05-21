#include "global.hpp"

void int_handler(int)
{
    kill(0, SIGKILL);
    close(server_socket);
    std::cout << "\033[1;31m\n\n\tServer stopped\033[0;0m" << std::endl;
}
