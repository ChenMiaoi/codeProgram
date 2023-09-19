#include "../util.hpp"

namespace httplib {
    namespace detail {
        // template <typename T>
        // bool process_server_socket(const std::atomic<socket_t>& svr_sock, socket_t sock, size_t keep_alive_max_count, time_t keep_alive_timeout_sec, 
        //     time_t read_timeout_sec, time_t read_timeout_usec, time_t write_timeout_sec, time_t write_timeout_usec, T callback) {
        //     return process_server_socket_core(svr_sock, sock, keep_alive_max_count, keep_alive_timeout_sec, 
        //         [&](bool close_connection, bool& connection_closed) {
        //             SocketStream strm(sock, read_timeout_sec, read_timeout_usec, write_timeout_sec, write_timeout_usec);
        //             return callback(strm, close_connection, connection_closed);
        //         });
        // }
    }
}