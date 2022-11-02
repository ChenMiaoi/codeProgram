#ifndef HTTPSERVER_TASK_HPP
#define HTTPSERVER_TASK_HPP

#include <iostream>
#include "../server_code/Protocol.hpp"

class Task {
public:
    Task() {}
    Task(int sock) : _sock(sock) {}
    ~Task() {}
public:
    void ProcessOn() { // 处理任务
        _handler(_sock);
    }
private:
     int _sock;
     CallBack _handler;  //设置回调
};

#endif //HTTPSERVER_TASK_HPP
