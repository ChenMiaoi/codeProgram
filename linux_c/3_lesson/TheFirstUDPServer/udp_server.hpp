#ifndef INC_3_LESSON_UDP_SERVER_HPP
#define INC_3_LESSON_UDP_SERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include  <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DEFAULT 8081
#define SIZE 128

class UdpServer{
public:
    UdpServer(int port = DEFAULT) :_port(port), _sockfd(-1){

    }
    ~UdpServer(){
        if (_sockfd >= 0){
            close(_sockfd);
        }
    }
public:
    bool InitUdpServer(){
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0){
            std::cerr << "socket error" << std::endl;
            return false;
        }
        std::cout << "socket create successfully! sockfd : " << _sockfd << std::endl;

        struct sockaddr_in local;
        memset(&local, '\0', sizeof(local));
        local.sin_family = AF_INET; //协议家族
        local.sin_port = htons(_port);     //端口号设置，port需要发送到网络中，所以要转化成网络序列
        //local.sin_addr.s_addr = inet_addr(_ip.c_str());     //IP的设置， 字符串IP需要转化为整形IP
        local.sin_addr.s_addr = INADDR_ANY;
        if (bind(_sockfd, (struct sockaddr*)&local, sizeof(local)) < 0){
            std::cerr << "bind error" << std::endl;
        }
        std::cout << "bind successfully!" << std::endl;

        return true;
    }
    void Start(){
        char buffer[SIZE] = {};
        while (true){
            struct sockaddr_in peer;    //对端
            socklen_t len = sizeof(peer);
            ssize_t size = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&peer, &len);
            if (size >  0){
                buffer[size] = 0;
                int port_ = ntohs(peer.sin_port);   //对端的端口号,从网络序列转化为主机序列
                std::string ip_ = inet_ntoa(peer.sin_addr);    //对端的IP,从整形IP转化为字符串IP

                std::string cmd = buffer;
                std::string result;
                if (cmd == "ls"){
                    int pipes[2];
                    pipe(pipes);
                    pid_t id = fork();
                    if (id == 0){
                        //child
                        close(pipes[0]);
                        dup2(pipes[1], 1);
                        execl("/usr/bin/ls", "ls", "-a", "-l", "-i", nullptr);
                        exit(1);
                    }
                    close(pipes[1]);
                    char c;
                    while (true){
                        if (read(pipes[0], &c, 1) > 0){
                            result.push_back(c);
                        }
                        else {
                            break;
                        }
                    }
                    wait(nullptr);
                }
                std::cout << "[ " << ip_ << " ] : " << port_ << "# " << buffer << std::endl;
                std::string echo_msg;
                if (result.empty()) {
                    echo_msg += buffer;
                    echo_msg = "server recieve -> ";
                }
                else {
                    echo_msg = result;
                }
                sendto(_sockfd, echo_msg.c_str(), echo_msg.size(), 0, (struct sockaddr*)&peer,  len);
            }
            else{
                std::cerr << "recvfrom error" << std::endl;
            }
        }
    }
private:
    int _port;  //端口
    //std::string _ip; //去掉
    int _sockfd;    //sock文件描述符
};
#endif //INC_3_LESSON_UDP_SERVER_HPP
