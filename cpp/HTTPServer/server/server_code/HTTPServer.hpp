#ifndef HTTPSERVER_HTTPSERVER_HPP
#define HTTPSERVER_HTTPSERVER_HPP

#include <iostream>
#include <thread>
#include <signal.h>
#include <pthread.h>
#include "TCPServer.hpp"
#include "../pool/Task.hpp"
#include "../pool/ThreadPool.hpp"
#include "../src/Log.hpp"

#define PORT 8081

class HTTPServer {
public:
    HTTPServer(int port = PORT) : _port(port), _stop(false) {}
    ~HTTPServer() {}
public:
    void InitServer() {
        //信号SIGPIPE需要忽略，不然在写入时会有可能崩溃
        signal(SIGPIPE, SIG_IGN);
        //_tcp_server = TCPServer::GetInstance(_port);
    }

    void Loop() {
        TCPServer* tsvr = TCPServer::GetInstance(_port);
        LOG(INFO, "Loop begin!");
        while (!_stop) {
            struct sockaddr_in peer;
            socklen_t len = sizeof (peer);
            int sock = accept(tsvr->Sock(), (struct sockaddr*)&peer, &len);
            if (sock < 0) {
                continue;
            }
            LOG(INFO, "get a new link");
            Task task(sock);
            ThreadPool::getInstance()->PushTask(task);
            /*
            int* sock_temp = new int (sock);
            std::thread td(Entrance::HandlerRequest, sock_temp);
            td.detach();
             */
        }// end while
    }
private:
    int _port;
    bool _stop;
};

#endif //HTTPSERVER_HTTPSERVER_HPP
