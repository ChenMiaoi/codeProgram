cmake_minimum_required(VERSION 3.22)
project(tinyhttp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 11)

add_executable(tinyhttp server.cc server.h)
