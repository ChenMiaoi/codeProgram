cmake_minimum_required(VERSION 3.16)
project(course02)

set(CMAKE_CXX_STANDARD 17)
add_executable(image01 image01.cc)
add_executable(image02 image02.cc)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(image01 ${OpenCV_LIBS})
target_link_libraries(image02 ${OpenCV_LIBS})
