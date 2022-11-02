#ifndef THEFIRSTTCPSERVER_TCP_SEVRER_HPP
#define THEFIRSTTCPSERVER_TCP_SEVRER_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include "ThreadPool.hpp"
#include "Task.hpp"

#define BACKLOG 5

struct Prama{
    Prama(int sock, std::string ip, int port)
        : _sock(sock)
        , _ip(ip)
        , _port(port)
    {}
    ~Prama(){}
    int _sock;
    std::string _ip;
    int _port;
};

class TcpServer{
public:
    TcpServer(int port) : _port(port), _sock_listen(-1), tp(nullptr)
    {}

    ~TcpServer(){
        if (_sock_listen >= 0){
            close(_sock_listen);
        }
    }
public:
    bool InitTcpServer(){
        _sock_listen = socket(AF_INET, SOCK_STREAM, 0);
        if (_sock_listen < 0){
            std::cerr << "socket error!" << std::endl;
            perror("socket");
            return false;
        }

        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port  = htons(_port);
        local.sin_addr.s_addr = INADDR_ANY;

        if (bind(_sock_listen, (struct sockaddr*)&local, sizeof(local)) < 0){
            std::cerr  << "bind  error" << std::endl;
            perror("bind");
            return false;
        }

        if (listen(_sock_listen, BACKLOG) < 0) {
            std::cerr << "listen  error" << std::endl;
            perror("listen");
            return false;
        }
        tp = new ThreadPool<Task> ();
        return true;
    }
#if 0
    static void* HanderRequest(void* arg){
        Prama *p = (Prama*)arg;
        pthread_detach(pthread_self());
        Service(p->_sock, p->_ip, p->_port);
        close(p->_sock);
        delete p;
        return nullptr;
    }
#endif

    void Loop(){
        //signal(SIGCHLD, SIG_IGN); 第一种方法
        tp->ThreadPoolInit();
        while (true){
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int sock = accept(_sock_listen, (struct sockaddr*)&peer, &len);
            if (sock < 0){
                std::cerr << "accept error" << std::endl;
                perror("accept");
                continue;
            }
            std::string ip = inet_ntoa(peer.sin_addr);
            int port = ntohs(peer.sin_port);
            Task t(sock, ip, port);
            tp->Put(t);
#if 0
            pthread_t tid;
            std::string ip = inet_ntoa(peer.sin_addr);
            int port = ntohs(peer.sin_port);
            Prama *p = new Prama(sock, ip, port);
            pthread_create(&tid, nullptr, HanderRequest, p);
#endif // !0

#if 0
            pid_t id = fork();
            if (id == 0){   //child
                close(_sock_listen);    //不必要必须关闭，一般建议关闭
                if (fork() > 0){    //为什么这样
                    exit(0);
                }
                std::string ip = inet_ntoa(peer.sin_addr);
                int port = ntohs(peer.sin_port);
                std::cout << "get a new link -> " << sock << " [ " << inet_ntoa(peer.sin_addr) << " ] : " << ntohs(peer.sin_port) << std::endl;
                Service(sock, ip, port);    //使其变成孤儿进程，把回收他的工作交给操作系统
                exit(0);
            }
            //waitpid();  //是阻塞的
            close(sock);    //必须关闭
            waitpid(id, nullptr, 0);
#endif // !0 多进程方案
        }
    }

#if 0
    static void Service(int sock, const std::string& ip, const int port){
        char buffer[1024] = {};
        while (true){
            ssize_t size = read(sock, buffer, sizeof(buffer) - 1);
            if (size > 0){
                buffer[size] = 0;
                std::cout <<"[ " << ip << " ] : " << port << "# " << buffer << std::endl;
                write(sock, buffer, size);
            } else if (size == 0){
                std::cout <<"[ " << ip << "] : " << port << "# close!" << std::endl;
                break;
            } else {
                std::cerr << sock << " read error" << std::endl;
                perror("read");
            }
        }
        std::cout << "service done!" << std::endl;
    }
#endif

private:
    int _port;
    int _sock_listen;
    ThreadPool<Task> *tp;
};

#endif //THEFIRSTTCPSERVER_TCP_SEVRER_HPP
