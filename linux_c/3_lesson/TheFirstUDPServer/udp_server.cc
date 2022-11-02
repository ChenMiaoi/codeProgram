#include "udp_server.hpp"

//udp_server port

int main(int argc, char* argv[]){
    //参数必须为2
    if (argc != 2){
        std::cerr << "Usage : " << argv[0] << " port " << std::endl;
        return 1;
    }
    //std::string ip = "127.0.0.1";   //127.0.0.1 == localhost：表示本主机：本地环回
    int port = atoi(argv[1]);   //将字符串转化为整数
    UdpServer* svr = new UdpServer(port);
    svr->InitUdpServer();

    svr->Start();
    return 0;
}