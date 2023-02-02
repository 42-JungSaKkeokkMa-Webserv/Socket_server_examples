#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

class ServerManager {
    private :
        int                     port;
        int                     socketfd;
        struct sockaddr_in      address;
    
    public :
        void    configureServer(void);
        void    listenClientRequest(void);

        void    setPort(int port);
        int     getPort(void);
        int     getSocketfd(void);
};

#endif