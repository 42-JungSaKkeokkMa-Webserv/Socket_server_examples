#include "../includes/libft.hpp"
#include "../includes/ServerManager.hpp"
#include "../includes/SelectPool.hpp"

// #define USAGE_ERROR "Usage: ./webserv [port]"
#define DEFAULT_PORT 8080

int main(void) {
    ServerManager server;
    server.setPort(DEFAULT_PORT);

    // if (argc != 2)
    //     strerr_exit(USAGE_ERROR);
    // else
    //     server.setPort(atoi(argv[1]));
    server.configureServer();
    server.listenClientRequest();

    SelectPool  select_pool(server.getSocketfd());
    select_pool.run();
    return 0;
}