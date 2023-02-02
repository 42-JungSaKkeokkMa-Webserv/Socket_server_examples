#include "../includes/ClientManager.hpp"
#include "../includes/libft.hpp"

using namespace std;

#define ERRMSG_CLIENT_NOT_FOUND "Warning : Client not found"

void ClientManager::addClient(ClientInfo& client) {
    clientList.insert(std::pair<int, ClientInfo>(client.getFd(), client));
}

void ClientManager::removeClient(int clientfd) {
    clientList.erase(clientfd);
}

/* 
이 함수는 무조건 Client가 추가된 상황을 전제로 합니다 
따라서 구현이 완료되었을 시에 find(fd) == end()를 체크하여
fail 상황을 체크하는 로직을 삭제해주세요.
*/
ClientInfo& ClientManager::searchClientByFd(int clientfd) {
    if (clientList.find(clientfd) == clientList.end()) {
        strerr_exit(ERRMSG_CLIENT_NOT_FOUND);
    }
    cout << "clientList.find(clientfd)->second.getFd() : " << clientList.find(clientfd)->second.getFd() << endl;
    return clientList.find(clientfd)->second;
}

// Path: srcs/ClientManager.cpp