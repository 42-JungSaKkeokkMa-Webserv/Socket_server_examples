#include "../includes/ServerManager.hpp"
#include "../includes/libft.hpp"

#define ERRMSG_SOCKET "Error: socket() failed"
#define ERRMSG_SETSOCKOPT "Error: setsockopt() failed"
#define ERRMSG_BIND "Error: bind() failed"
#define ERRMSG_LISTEN "Error: listen() failed"

void ServerManager::configureServer(void) {
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd < 0) strerr_exit(ERRMSG_SOCKET);

    bzero(&this->address, sizeof(this->address));
    int opt = 1;
    if (setsockopt(this->socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        strerr_exit(ERRMSG_SETSOCKOPT);
    
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
    this->address.sin_port = htons(this->getPort());
    
    int bind_result = bind(this->socketfd, (const struct sockaddr *)&this->address, sizeof(this->address));
    if (bind_result < 0) strerr_exit(ERRMSG_BIND);
}

void ServerManager::listenClientRequest(void) {
    int listen_result = listen(this->socketfd, SOMAXCONN);
    if (listen_result < 0) {
        strerr_exit(ERRMSG_LISTEN);
    } else {
        std::cout << "Server is listening on port " << this->getPort() << " . . . " << std::endl;
    }
}

void ServerManager::setPort(int port) {
    this->port = port;
}

int ServerManager::getPort(void) {
    return this->port;
}

int ServerManager::getSocketfd(void) {
    return this->socketfd;
}

// Path: includes/ServerManager.hpp