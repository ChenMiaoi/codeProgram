#include <iostream>
#include <string>
#include <memory>
#include "./server_code/HTTPServer.hpp"

static void Usage(const std::string& proc) {
    std::cout << "Usage: \n\t" << proc << " port" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        Usage(argv[0]);
        exit(4);
    }

    int port = atoi(argv[1]);

    std::shared_ptr<HTTPServer> http_server(new HTTPServer(port));

    http_server->InitServer();
    http_server->Loop();
    return 0;
}
