#ifndef INC_3_LESSON_UDP_CLIENT_HPP
#define INC_3_LESSON_UDP_CLIENT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class UdpClient{
public:
    UdpClient(std::string ip, int port)
        : _server_ip(ip)
        , _server_port(port)
    {}

    ~UdpClient(){
        if (_sockfd >= 0){
            close(_sockfd);
        }
    }
public:
    bool InitUdpClient(){
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0){
            std::cerr << "socket error!" << std::endl;
            return false;
        }
        return true;
    }
    void Start(){
        struct sockaddr_in peer;
        memset(&peer, 0, sizeof(peer));
        peer.sin_family = AF_INET;
        peer.sin_port = htons(_server_port);
        peer.sin_addr.s_addr = inet_addr(_server_ip.c_str());
        std::string msg;
        while (true){
            std::cout << "please enter what you want# ";
            std::cin >> msg;
            sendto(_sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
            char buffer[128];
            struct sockaddr_in temp;
            socklen_t len = sizeof(temp);
            ssize_t size = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&temp, &len);
            if (size > 0){
                buffer[size] = 0;
                std::cout << buffer << std::endl;
            }
        }
    }
private:
    int _sockfd;
    std::string _server_ip;     //服务器的ip地址
    int _server_port;   //服务器的端口号
};
#endif //INC_3_LESSON_UDP_CLIENT_HPP
