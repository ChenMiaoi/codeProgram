cmake_minimum_required(VERSION 3.22)
project(CppStd11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_executable(cpp11_1 cpp11/main.cc)
add_executable(cpp11_2 cpp11/test.cc)
add_executable(cpp11_3 cpp11/template.cc)

add_executable(Atour_1 Atour/main.cc)
add_executable(Atour_2 Atour/UserDefinedType.cc)