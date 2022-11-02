#ifndef TINYHTTP_SERVER_H
#define TINYHTTP_SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_MSG "Server: ChenMiaoi/0.1.0\r\n"

void error_die(const std::string& warning) {
    perror(warning.c_str());
    exit(1);
}

size_t StartUp(u_short& port){
    int httpd = 0;
    if ((httpd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        error_die("socket");
    }

    struct sockaddr_in peer;
    memset(&peer, '\0', sizeof(peer));
    peer.sin_family = AF_INET;
    peer.sin_port = htonl(port);
    peer.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(httpd, (struct sockaddr*)&peer, sizeof(peer)) < 0) {
        error_die("bind");
    }
    if (port == 0) {
        socklen_t peer_len = sizeof(peer);
        // 调用getsockname()手动的获取系统给httpd随机分配的端口号
        if (getsockname(httpd, (struct sockaddr*)&peer, &peer_len) == -1) {
            error_die("getsockname");
            port = ntohs(peer.sin_port);
        }
    }

    if (listen(httpd, 5) < 0) {
        error_die("listen");
    }

    return httpd;
}

size_t get_line(int sock, char* buf);
#define BUF_SIZE 1024
#define METHOD_SIZE 255
#define URL_SIZE 255
#define PATH_SIZE 512

void AcceptRequest(int client_sock) {
    char buf[BUF_SIZE];
    size_t num_chars;
    char method[METHOD_SIZE];
    char url[URL_SIZE];
    char path[PATH_SIZE];
    num_chars = get_line(client_sock, buf);
    std::cout << buf << std::endl;
}

size_t get_line(int sock, char* buf) {
    size_t count = 0;
    char msg = '\0';
    while ((count < BUF_SIZE - 1) && (msg != '\n')) {
        if (recv(sock, &msg, 1, 0) > 0) {
            if (msg == '\r') {
                if ((recv(sock, &msg, 1, MSG_PEEK) > 0) && (msg == '\n')) {
                    recv(sock, &msg, 1, 0);
                }else {
                    msg = '\n';
                }
            }
            buf[count++] = msg;
        }else {
            msg = '\n';
        }
    }
    buf[count] = '\0';
    return count;
}
#endif //TINYHTTP_SERVER_H
