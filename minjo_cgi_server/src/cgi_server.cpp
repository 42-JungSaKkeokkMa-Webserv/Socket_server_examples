#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

using namespace std;

int main() {
    // 소켓 생성
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 소켓 설정
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    // 소켓 바인딩
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 연결 요청 대기
    listen(server_socket, 5);

    while (true) {
        // 클라이언트 요청 수락
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

        // 클라이언트 요청 처리
        char request[1024];
        read(client_socket, request, sizeof(request)-1);
        cout << "Client Request: " << request << endl;

        // CGI 실행
        int pid = fork();
        if (pid == 0) {
            // Child process
            // CGI 스크립트 경로 설정
            const char *cgi_script_path = "/path/to/script.cgi";
            // 환경 변수 설정
            setenv("REQUEST_METHOD", "GET", 1);
            setenv("QUERY_STRING", "param1=value1&param2=value2", 1);
            // 스크립트 실행
            dup2(client_socket, STDOUT_FILENO);
            execl(cgi_script_path, cgi_script_path, NULL);
        } else {
            // Parent process
            // 자식 프로세스 종료 기다리기
            waitpid(pid, NULL, 0);
        }

        // 소켓 닫기
        close(client_socket);
    }
    return 0;
}