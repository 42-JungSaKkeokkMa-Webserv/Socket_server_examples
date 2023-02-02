#ifndef SELECTPOOL_HPP
#define SELECTPOOL_HPP

#include <sys/select.h>
#include <sys/socket.h>
#include "ClientManager.hpp"

#define ERRMSG_SELECT_FAILED "Error: select() failed"
#define ERRMSG_SELECT_TIMEOUT "Error: select() timeout"
#define ERRMSG_ACCEPT_FAILED "Error: accept() failed"

class SelectPool {
    private :
        int     server_socketfd;
        int     maxfd;
        fd_set  readfds;
        fd_set  writefds;
        fd_set  activefds;
        ClientManager   clientManager;
        SelectPool();

    public :
        SelectPool(int server_socketfd);
        void    registerClient(ClientInfo& clientfd);
        void    unregisterClient(int clientfd);
        void    refreshSelectPoolStatus(void);
        void    run(void);

        int     getServerSocketfd(void);
        bool    isReadable(int fd);
        bool    isWritable(int fd);
        void    acceptClient(void);
};

#endif