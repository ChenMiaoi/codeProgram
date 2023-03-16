cmake_minimum_required(VERSION 3.0.0)
project(day3 VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)

add_executable(exit exit.c)
add_executable(_exit _exit.c)
add_executable(wait wait.c)
add_executable(waitpid waitpid.cc)
add_executable(exec exec.c)