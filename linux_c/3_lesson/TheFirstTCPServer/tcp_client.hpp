#ifndef THEFIRSTTCPSERVER_TCP_CLIENT_HPP
#define THEFIRSTTCPSERVER_TCP_CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class TcpClient{
public:
    TcpClient(std::string ip, int port) :_svr_ip(ip), _svr_port(port), _sock(-1)
    {}

    ~TcpClient(){
        if (_sock >= 0){
            close(_sock);
        }
    }
public:
    bool InitTcpClient(){
        _sock = socket(AF_INET, SOCK_STREAM, 0);
        if (_sock < 0){
            std::cerr << "socket error" << std::endl;
            perror("socket");
            return false;
        }
        return true;
    }
    void Start(){
        struct sockaddr_in peer;
        memset(&peer, 0, sizeof(peer));
        peer.sin_family = AF_INET;
        peer.sin_port = htons(_svr_port);
        peer.sin_addr.s_addr = inet_addr(_svr_ip.c_str());
        if (connect(_sock, (struct sockaddr*)&peer, sizeof(peer)) == 0){
            std::cout << "connect success..." << std::endl;
            Request(_sock);
        } else {
            std::cerr << "connet error" << std::endl;
            perror("connect");
            exit(1);
        }
    }
    void Request(int sock){
        std::string msg;
        char buffer[1024] = {};
        while (true){
            std::cout << "Please Enter# " ;
            std::cin >> msg;
            write(sock, msg.c_str(), msg.size());
            ssize_t s = read(sock, buffer, sizeof(buffer) - 1);
            if (s > 0){
                buffer[s] = 0;
            }
            std::cout << "[ server echo ]# " << buffer << std::endl;
        }
    }
private:
    std::string _svr_ip;
    int _svr_port;
    int _sock;
};

#endif //THEFIRSTTCPSERVER_TCP_CLIENT_HPP
