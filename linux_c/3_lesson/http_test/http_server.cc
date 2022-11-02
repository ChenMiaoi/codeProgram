#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

int main(){
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0){
        perror("socket error");
        return 1;
    }

    int flag = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(8081);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        perror("bind error");
        return 2;
    }
    if (listen(listen_sock, 5) < 0){
        perror("listen error");
        return 3;
    }

    struct sockaddr_in peer;
    for (; ;){
        socklen_t len = sizeof(peer);
        int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
        if (sock < 0){
            perror("accept error");
            continue;
        }
        if (fork() == 0){
            if (fork() > 0){
                exit(0);
            }
            close(listen_sock);
            //read http request
            char buffer[1024] = {};
            recv(sock, buffer, sizeof(buffer), 0);
            std::cout << "######################## http request begin #############################" << std::endl;
            std::cout << buffer << std::endl;
            std::cout << "#######################-# http request end   #############################" << std::endl;

            std::cout << "######################## http response begin #############################" << std::endl;
#define PAGE "./idex.html"
            std::ifstream in(PAGE);
            if (in.is_open()){
                in.seekg(0, std::ios::end);
                size_t lens = in.tellg();
                in.seekg(0, std::ios::beg);
                char* file = new char[lens];
                in.read(file, lens);
                in.close();

                //std::string status_line = "http/1.1 307 Temporary Redirect\r\n";
                std::string status_line = "http/1.1 200 OK\r\n";
                std::string response_header = "Content-Length: " + std::to_string(lens);
                response_header += "\r\n";
                response_header += "Set-Cookie: abcdefg12345\r\n";
                //response_header += "location: https://qq.com//\r\n";
                std::string blank = "\r\n";
                //std::string total = status_line + response_header + blank;
                send(sock, status_line.c_str(), status_line.size(), 0);
                send(sock, response_header.c_str(), response_header.size(), 0);
                send(sock, blank.c_str(), blank.size(), 0);
                //send(sock, total.c_str(), total.size(), 0);
                send(sock, file, lens, 0);
                std::cout << "######################## http response end #############################" << std::endl;
                delete[] file;
            }
            close(sock);
            exit(0);
        }
        waitpid(-1, nullptr, 0);
    }
    return 0;
}