#include "server.h"

int main() {
    int server_sock = -1;
    int client_sock = -1;
    u_short port = 0;

    struct sockaddr_in peer; // 客户端的协议簇
    socklen_t peer_len = sizeof(peer);

    server_sock = StartUp(port);
//    std::cout << server_sock << std::endl;
//    std::cout << port << std::endl;

    std::cout << "The httpd running on port " << port << std::endl;

    while (true) {
        if ((client_sock = accept(server_sock, (struct sockaddr*)&peer, &peer_len)) == -1) {
            error_die("accept");
        }
        AcceptRequest(client_sock);
        close(server_sock);
    }
    return 0;
}
