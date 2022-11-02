cmake_minimum_required(VERSION 3.22)
project(3_lesson/TheFirstUDPServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(3_lesson
        TheFirstUDPServer/udp_client.cc TheFirstUDPServer/udp_server.cc TheFirstUDPServer/udp_server.cc)

add_executable(udp_client TheFirstUDPServer/udp_client.cc)
add_executable(udp_server TheFirstUDPServer/udp_server.cc)