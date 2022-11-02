cmake_minimum_required(VERSION 3.23)
project(TicketSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(TicketSystem main.cc include/Util.h src/Util.cc include/allInc.h src/ticket.cc include/ticket.h)
