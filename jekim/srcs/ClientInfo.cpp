#include "../includes/libft.hpp"
#include "../includes/ClientInfo.hpp"
#include <iostream>
#include <sys/socket.h>

using namespace std;

ClientInfo::ClientInfo(int fd, struct sockaddr_in address, int add_len) {
    this->fd = fd;
    this->address = address;
    this->add_len = add_len;
    memset(buffer, 0, sizeof(buffer));
}

int ClientInfo::getFd(void) {
    return this->fd;
}

char* ClientInfo::getBuffer(void) {
    return this->buffer;
}

void ClientInfo::readRequest(void) {
    recv(this->fd, this->buffer, BUFFER_SIZE, 0);
    cout << "read from client: " << this->buffer << endl;
}

void ClientInfo::writeResponse(void) {
    send(this->fd, this->buffer, BUFFER_SIZE, 0);
    cout << "write to client: " << this->buffer << endl;
}