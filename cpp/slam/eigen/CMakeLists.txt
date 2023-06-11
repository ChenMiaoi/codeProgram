cmake_minimum_required(VERSION 3.16)
project(eigen)

set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cc)
add_executable(geometry geometry.cc)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})