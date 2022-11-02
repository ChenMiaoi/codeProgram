#include "tcp_sevrer.hpp"

// ./server port

void Usage(std::string proc){
    std::cerr << "Usage : " << proc << " port " << std::endl;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        Usage(argv[0]);
        perror("argv");
        exit(2);
    }

    TcpServer tsvr(atoi(argv[1]));
    if (tsvr.InitTcpServer()) {
        tsvr.Loop();
    }
    return 0;
}