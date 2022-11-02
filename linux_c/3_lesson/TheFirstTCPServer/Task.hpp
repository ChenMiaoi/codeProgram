#ifndef THEFIRSTTCPSERVER_TASK_HPP
#define THEFIRSTTCPSERVER_TASK_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <unordered_map>

class Handler{
public:
    Handler(){}
    ~Handler(){}

    void operator()(int sock, std::string ip, int port){
        std::unordered_map<std::string, std::string> dict;
        dict.insert(std::make_pair("apple", "苹果"));
        dict.insert(std::make_pair("banana", "香蕉"));
        dict.insert(std::make_pair("boy", "男孩"));

        char buffer[1024] = {};
        std::string value;
        while (true){
            ssize_t size = read(sock, buffer, sizeof(buffer) - 1);
            if (size > 0){
                buffer[size] = 0;
                std::cout <<"[ " << ip << " ] : " << port << "# " << buffer << std::endl;
                std::string key = buffer;
                auto iter = dict.find(key);
                if (iter != dict.end()){
                    value = iter->second;
                }else {
                    value = buffer;
                }
                write(sock, value.c_str(), value.size());
            } else if (size == 0){
                std::cout <<"[ " << ip << "] : " << port << "# close!" << std::endl;
                break;
            } else {
                std::cerr << sock << " read error" << std::endl;
                perror("read");
            }
        }
        std::cout << "service done!" << std::endl;
        close(sock);
    }
};

class Task{
public:
    Task(){}

    Task(int sock, std::string ip, int port)
        : _sock(sock)
        , _ip(ip)
        , _port(port)
    {}

private:
    int _sock;
    std::string _ip;
    int _port;
    Handler handler;
};

#endif //THEFIRSTTCPSERVER_TASK_HPP
