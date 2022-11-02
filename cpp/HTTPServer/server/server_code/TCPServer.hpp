#ifndef HTTPSERVER_TCPSERVER_HPP
#define HTTPSERVER_TCPSERVER_HPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <mutex>
#include "../src/Log.hpp"

#define BACK_LOG 5

class TCPServer {
private:
    TCPServer(int port) : _port(port), _listen_sock(-1) {}
    TCPServer(const TCPServer& s) {}
public:
    ~TCPServer() { if (_listen_sock >= 0) close(_listen_sock); }
public:
    static TCPServer* GetInstance(int port) {
        static std::mutex _lock;
        // static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
        if (nullptr == svr) {
            _lock.lock();
            // pthread_mutex_lock(&lock);
            if (nullptr == svr) {
                svr = new TCPServer(port);
                svr->InitServer();
            }// end if
            _lock.unlock();
            // pthread_mutex_unlock(&lock);
        }// end if
        return svr;
    }
    void InitServer() {
        Socket();
        Bind();
        Listen();
        LOG(INFO, "TCP server init ... success!");
    }

    void Socket() {
        _listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (_listen_sock < 0) {
            LOG(FATAL, "socket error!");
            exit(1);
        }
        //地址复用，防止链接突然的断开导致无法立即重启服务器
        int opt = 1;
        setsockopt(_listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        LOG(INFO, "create socket ... success!");
    }

    void Bind() {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));

        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = htons(_port);
        if (bind(_listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0) {
            LOG(FATAL, "bind error!");
            exit(2);
        }
        LOG(INFO, "bind socket ... success!");
    }

    void Listen() {
        if (listen(_listen_sock, BACK_LOG) < 0) {
            LOG(FATAL, "listen error!");
            exit(3);
        }
        LOG(INFO, "listen socket ... success!");
    }

    int Sock() {
        return _listen_sock;
    }
private:

private:
    int _port;
    int _listen_sock;
    static TCPServer* svr;
};

TCPServer* TCPServer::svr = nullptr;

#endif //HTTPSERVER_TCPSERVER_HPP
