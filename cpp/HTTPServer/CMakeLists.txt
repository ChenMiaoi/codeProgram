cmake_minimum_required(VERSION 3.23)
project(HTTPServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 11)

add_executable(HTTPServer server/main.cc
        server/server_code/TCPServer.hpp server/server_code/HTTPServer.hpp server/server_code/Protocol.hpp
        server/src/Log.hpp   server/src/Util.hpp server/pool/Task.hpp server/pool/ThreadPool.hpp)

add_executable(HTTPCGI server/cgi/test_cgi.cc)

include_directories("mysqldb/include")
link_directories(mysqldb/lib)
link_libraries(libmysqlclient)
target_link_libraries(HTTPServer libmysqlclient)

add_executable(DB server/cgi/db_conn.cc)
