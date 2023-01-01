cmake_minimum_required(VERSION 3.22)
project(Atour)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

add_executable(Atour_1 main.cc)
add_executable(Atour_2 UserDefinedType.cc)
add_executable(Atour_3 Modularity.cc
        Vector/Vector.cc Vector/Vector.h)
add_executable(Atour_4 model/Vector.cc model/Vector.cppm model/vector_printer.cpp)
add_executable(Atour_5 structuredBinding.cc)
add_executable(Atour_6 ErrorException.cc Vector/Vector.cc Vector/Vector.h)
add_executable(Atour_7 ConcreteType.cc)
add_executable(Atour_8 EssentialOperations.cc
        Operation-Vector/Vector.cc Operation-Vector/Vector.h)
add_executable(Atour_9 Templates.cc)