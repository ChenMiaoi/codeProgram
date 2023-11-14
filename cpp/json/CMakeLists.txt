cmake_minimum_required(VERSION 3.20)
project(json VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND custom_compiler_flags
    -std=c++17
    -pedantic
    -Wall
    -Wextra
    -Werror
    -Wstrict-prototypes
    -Wwrite-strings
    -Wshadow
    -Winit-self
    -Wcast-align
    -Wformat=2
    -Wmissing-prototypes
    -Wstrict-overflow=2
    -Wcast-qual
    -Wundef
    -Wswitch-default
    -Wconversion
    -Wc++-compat
    -fstack-protector-strong
    -Wcomma
    -Wdouble-promotion
    -Wparentheses
    -Wformat-overflow
    -Wunused-macros
    -Wmissing-variable-declarations
    -Wused-but-marked-unused
    -Wswitch-enum
)

add_library(json STATIC src/json.cc)
add_library(bf   STATIC src/buffer.cc)
add_library(hk   STATIC src/hooks.cc)
add_library(err  STATIC src/error.cc)

add_executable(main main.cc)

target_link_libraries(
    main json bf hk err
)

# add_custom_target(json_clean
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
#     COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
#     COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
#     COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
#     COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/main
#     COMMENT "Clean project"
# )