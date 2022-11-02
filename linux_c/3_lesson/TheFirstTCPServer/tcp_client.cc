#include "tcp_client.hpp"

// ./client ip port

void Usage(std::string proc){
    std::cout << "Usage : " << proc << " server_ip " << " server_port " << std::endl;
}
int main(int argc, char* argv[]){
    if (argc != 3){
        Usage(argv[0]);
        perror("argv");
        exit(1);
    }

    TcpClient tcl(argv[1], atoi(argv[2]));
    if (tcl.InitTcpClient()){
        tcl.Start();
    }

    return 0;
}