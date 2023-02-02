#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <map>
#include "ClientInfo.hpp"

/*
해당 객체는 여러 Client를 등록하고 이를 fd 기반으로 탐색하고 다루는 객체입니다
만약 여러분이 채팅 서버처럼 다중 클라이언트에 대해서 관리해야 한다면
다음과 같이 다수의 Client를 관리하는 옵저버 패턴을 구현하시면 됩니다.

지금 예제에서는 간단하게 등록만 하고 제거하기 때문에 실제적으로 필요하다고 느껴지지는 않을 것입니다
이런 식으로 관리하는구나 정도로만 이해하시면 됩니다
*/
class ClientManager {
    private :
        std::map<int, ClientInfo>   clientList;

    public :
        void            addClient(int clientfd);
        void            addClient(ClientInfo& client);
        void            removeClient(int clientfd);
        ClientInfo&     searchClientByFd(int clientfd);
};

#endif