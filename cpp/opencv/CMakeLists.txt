cmake_minimum_required(VERSION 3.16)
project(opencv)

set(CMAKE_CXX_STANDARD 17)
add_executable(test main.cc)

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(
            test
            ${OpenCV_LIBS}
    )
else (OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif (OpenCV_FOUND)