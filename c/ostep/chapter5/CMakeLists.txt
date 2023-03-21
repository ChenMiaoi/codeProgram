cmake_minimum_required(VERSION 3.0.0)
project(chapter5 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ex01 ex01.c)
add_executable(ex02 ex02.c)
add_executable(ex03 ex03.c)
add_executable(ex04 ex04.c)
add_executable(ex05 ex05.c)
add_executable(ex06 ex06.c)
add_executable(ex07 ex07.c)
add_executable(ex08 ex08.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
