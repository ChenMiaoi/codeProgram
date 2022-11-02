cmake_minimum_required(VERSION 3.22)
project(http_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 11)

add_executable(http_test http_server.cc)

add_executable(http_server http_server.cc)