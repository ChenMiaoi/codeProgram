cmake_minimum_required(VERSION 3.22)
project(rvc VERSION 0.1.0)

set(CMAKE_CXX_COMPILER g++)

set(FLAG "-O -g \
    -ansi -pedantic \
    -Wall -Wextra \
    -Wno-variadic-macro -Wno-maybe-uninitialized")
set(CMAKE_CXX_FLAGS "${FLAG} -std=c++17")
set(CMAKE_CXX_STANDARD_REQUIRED 11)

option(ENABLE_RISCV "Enable RISC-V architecture" ON)

if (ENABLE_RISCV)
    include(deps/cmake/riscv.cmake)
    set(CMAKE_C_COMPILER "riscv64-linux-gnu-gcc")
endif()

# set(CMAKE_C_FLAGS ${FLAG})
# add_custom_command(
#     OUTPUT ${CMAKE_BINARY_DIR}/libc.inc
#     COMMAND ${CMAKE_BINARY_DIR}/inliner src/lib/libc.c ${CMAKE_BINARY_DIR}/libc.inc
#     DEPENDS ${CMAKE_BINARY_DIR}/inliner src/lib/libc.c
#     COMMENT "Generating libc.inc"
# )
# add_custom_target(
#     generate_libc DEPENDS ${CMAKE_BINARY_DIR}/libc.inc
# )

set(SYMBOL src/symbol)
set(UTIL src/util)
set(DEFS src/def)

add_library(libps ${SYMBOL}/parse.cc)
add_library(libgb ${SYMBOL}/global.cc)
add_library(libut ${UTIL}/util.cc)
add_library(libdf ${DEFS}/defs.cc)

add_executable(miao src/main.cc)
# add_dependencies(miao generate_libc)

target_link_libraries(
    miao libgb libps libut libdf # libc.inc
)