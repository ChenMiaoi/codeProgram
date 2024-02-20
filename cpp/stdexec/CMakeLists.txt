cmake_minimum_required(VERSION 3.22.1)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

##########################################################################
# - Project definition ---------------------------------------------------

# Define the project and set the version and languages
if(NOT EXISTS ${CMAKE_BINARY_DIR}/execution.bs)
    file(DOWNLOAD "https://raw.githubusercontent.com/brycelelbach/wg21_p2300_execution/main/execution.bs"
        ${CMAKE_BINARY_DIR}/execution.bs)
endif()
file(STRINGS "${CMAKE_BINARY_DIR}/execution.bs" STD_EXECUTION_BS_REVISION_LINE REGEX "Revision: [0-9]+")
string(REGEX REPLACE "Revision: ([0-9]+)" "\\1" STD_EXECUTION_BS_REVISION ${STD_EXECUTION_BS_REVISION_LINE})

project(stdexec VERSION "0.${STD_EXECUTION_BS_REVISION}.0" LANGUAGES CXX)

# Print Cmake configuration
message(STATUS "System          : ${CMAKE_SYSTEM}")
message(STATUS "System name     : ${CMAKE_SYSTEM_NAME}")
message(STATUS "System ver      : ${CMAKE_SYSTEM_VERSION}")
message(STATUS)

# Set the version and current build date
set(STDEXEC_VERSION "${PROJECT_VERSION}")
set(STDEXEC_VERSION_MAJOR "${PROJECT_VERSIONB_MAJOR}")
string(TIMESTAMP STDEXEC_BUILD_DATE "%Y-%m-%d")
string(TIMESTAMP STDEXEC_BUILD_YEAR "%Y")

message(STATUS "Library ver     : ${STDEXEC_VERSION}")
message(STATUS "Build data      : ${STDEXEC_BUILD_DATE}")
message(STATUS "Build year      : ${STDEXEC_BUILD_YEAR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(EXEC_INCLUDE_ROOT "include/exec")
set(STDEXEC_INCLUDE_ROOT "include/stdexec")
#include_directories(${INCLUDE_ROOT})

file(GLOB_RECURSE EXEC_HEADERS ${EXEC_INCLUDE_ROOT}/*.hpp)
file(GLOB_RECURSE STDEXEC_HEADERS ${STDEXEC_INCLUDE_ROOT}/*.hpp)

#add_library(stdexec INTERFACE)
#target_sources(stdexec INTERFACE ${INCLUDE_HEADERS})

add_executable(main main.cc ${EXEC_HEADERS} ${STDEXEC_HEADERS})
#target_link_libraries(main stdexec)
