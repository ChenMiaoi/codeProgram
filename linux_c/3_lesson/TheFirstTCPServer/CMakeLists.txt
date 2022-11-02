cmake_minimum_required(VERSION 3.22)
project(TheFirstTCPServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TheFirstTCPServer
        Task.hpp
        tcp_client.cc
        tcp_client.hpp
        tcp_sevrer.cc
        tcp_sevrer.hpp)

add_executable(test test.cc)