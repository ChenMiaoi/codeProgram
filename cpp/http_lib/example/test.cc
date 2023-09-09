#include "include/request.hpp"

#include <iostream>

int main() {
    httplib::Request request;
    request._headers.insert({"http", "hello"});
    request._headers.insert({"https", "world"});

    if (request.has_header("http")) {
        std::cout << request.get_header_value("http") << std::endl;
    }
    return 0;
}