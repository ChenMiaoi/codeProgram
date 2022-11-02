cmake_minimum_required(VERSION 3.22)
project(NetCal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

add_executable(NetCal server.cc client.cc protocol.hpp)

add_executable(server server.cc)
add_executable(client client.cc)
add_executable(test test.c)