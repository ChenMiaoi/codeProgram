cmake_minimum_required(VERSION 3.22)
project(CppStd11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_executable(cpp11_1 cpp11/main.cc)
add_executable(cpp11_2 cpp11/test.cc)
add_executable(cpp11_3 cpp11/template.cc)

add_executable(Atour_1 Atour/main.cc)
add_executable(Atour_2 Atour/UserDefinedType.cc)
add_executable(Atour_3 Atour/Modularity.cc
        Atour/Vector/Vector.cc Atour/Vector/Vector.h)
add_executable(Atour_4 Atour/model/Vector.cc Atour/model/Vector.cppm Atour/model/vector_printer.cpp)
add_executable(Atour_5 Atour/structuredBinding.cc)
add_executable(Atour_6 Atour/ErrorException.cc Atour/Vector/Vector.cc Atour/Vector/Vector.h)
add_executable(Atour_7 Atour/ConcreteType.cc)