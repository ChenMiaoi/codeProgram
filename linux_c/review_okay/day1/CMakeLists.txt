cmake_minimum_required(VERSION 3.0.0)
project(day1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(main main.c)
add_executable(state state.c)
add_executable(zombie zombie.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
