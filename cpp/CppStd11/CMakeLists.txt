cmake_minimum_required(VERSION 3.22)
project(CppStd11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

add_executable(CppStd11 main.cc)

add_executable(main1 test.cc)