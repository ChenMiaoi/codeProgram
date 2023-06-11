cmake_minimum_required(VERSION 3.16)
project(course01)

add_executable(mat mat.cc)
add_executable(mat_op mat_op.cc)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(mat ${OpenCV_LIBS})
target_link_libraries(mat_op ${OpenCV_LIBS})