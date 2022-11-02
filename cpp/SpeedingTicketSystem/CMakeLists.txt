cmake_minimum_required(VERSION 3.23)
project(SpeedingTicketSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(SpeedingTicketSystem
        Driver.h Police.h Tickets.h System.h src.h
        main.cc )
