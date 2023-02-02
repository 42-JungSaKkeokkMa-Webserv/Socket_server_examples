#include "../includes/SelectPool.hpp"
#include "../includes/libft.hpp"
#include <unistd.h>

using namespace std;

SelectPool::SelectPool(int server_socketfd) : server_socketfd(server_socketfd) {
    this->maxfd = server_socketfd + 1;
    FD_ZERO(&this->activefds);
    FD_SET(server_socketfd, &this->activefds);
}

void SelectPool::acceptClient(void) {
    struct sockaddr_in  client_addr;
    socklen_t           client_addr_len = sizeof(client_addr);
    int clientfd = accept(this->getServerSocketfd(), (struct sockaddr*)&client_addr, &client_addr_len);
    if (clientfd < 0) {
        strerr_exit(ERRMSG_ACCEPT_FAILED);
    }
    ClientInfo client = ClientInfo(clientfd, client_addr, client_addr_len);
    this->registerClient(client);
    client.readRequest();
    client.writeResponse();
    this->unregisterClient(clientfd);
}

void SelectPool::registerClient(ClientInfo& client) {
    int clientfd = client.getFd();
    
    this->clientManager.addClient(client);
    FD_SET(clientfd, &this->activefds);
    if (clientfd > this->maxfd) {
        this->maxfd = clientfd + 1;
    }
}

void SelectPool::unregisterClient(int clientfd) {
    FD_CLR(clientfd, &this->activefds);
    this->clientManager.removeClient(clientfd);
    close(clientfd);
}

void SelectPool::refreshSelectPoolStatus(void) {
    this->readfds = this->writefds = this->activefds;
    int result = select(maxfd, &this->readfds, &this->writefds, NULL, NULL);
    if (result < 0) {
        strerr_exit(ERRMSG_SELECT_FAILED);
    } else if (result == 0) {
        strerr_exit(ERRMSG_SELECT_TIMEOUT);
    }
}

void SelectPool::run(void) {
    while (1) {
        this->refreshSelectPoolStatus();
        for (int fd = 0; fd < maxfd; fd++) {
            if (!isReadable(fd)) {
                continue ;
            }
            if (fd == this->getServerSocketfd()) {
                this->acceptClient();
            }
        }
    }
}

int SelectPool::getServerSocketfd(void) {
    return this->server_socketfd;
}

bool SelectPool::isReadable(int fd) {
    return FD_ISSET(fd, &this->readfds);
}

bool SelectPool::isWritable(int fd) {
    return FD_ISSET(fd, &this->writefds);
}