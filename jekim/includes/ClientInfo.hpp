#ifndef CLIENTINFO_HPP
#define CLIENTINFO_HPP

#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

class ClientInfo {
    private :
        int     fd;
        int     add_len;
        struct  sockaddr_in address;
        ClientInfo();
        char   buffer[BUFFER_SIZE + 1];

    public :
        ClientInfo(int fd, struct sockaddr_in address, int add_len);
        int     getFd(void);
        char*   getBuffer(void);

        void    readRequest(void);
        void    writeResponse(void);
};

#endif