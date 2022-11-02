#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include "protocol.hpp"

using namespace std;

void* Rountinue(void* arg){
    int sock = *(int*)arg;
    delete (int*)arg;

    while (true){
        request_t rq;
        response_t rsp = {0};
        ssize_t s = recv(sock, &rq, sizeof(rq), 0);
        if (s > 0){
            switch (rq.op) {
                case '+':
                    rsp.result = rq.x + rq.y;
                    break;
                case '-':
                    rsp.result = rq.x - rq.y;
                    break;
                case '*':
                    rsp.result = rq.x * rq.y;
                    break;
                case '/':
                    if (rq.y == 0){
                        rsp.code = 1;   //除数为零
                    }else {
                        rsp.result = rq.x / rq.y;
                    }
                    break;
                case '%':
                    if (rq.y == 0){
                        rsp.code = 2;   //模数为零
                    }else {
                        rsp.result = rq.x % rq.y;
                    }
                    break;
                default:
                    rsp.code = 3;   //非法运算
                    break;
            }
            send(sock, &rsp, sizeof(rsp), 0);
        }   //if end
        else if (s == 0){
            cout << "client quit" << endl;
            break;
        }
        else {
            break;
        }
    }   //while end
    return nullptr;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Usage : " << argv[0] << " port " << endl;
        exit(1);
    }
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0){
        perror("listen sock error");
        exit(2);
    }

    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        perror("bind error");
        exit(3);
    }
    if (listen(listen_sock, 5) < 0){
        perror("listen error");
        exit(4);
    }

    struct sockaddr_in peer;
    for (; ;){
        socklen_t len = sizeof(peer);
        int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
        if (sock < 0){
            perror("sock");
            continue;
        }
        pthread_t tid;
        int* p = new int(sock);
        pthread_create(&tid, nullptr, Rountinue, p);
    }
}