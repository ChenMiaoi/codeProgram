#ifndef __UTIL_H__
#define __UTIL_H__

#include "def.hpp"
#include "stream.hpp"
#include "data_deal/data_sink.hpp"

#include <cassert>
#include <chrono>
#include <algorithm>
#include <atomic>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iterator>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <thread>

namespace httplib {
    namespace detail {    
        inline bool has_header(const Headers& headers, const std::string& key) {
            return headers.find(key) != headers.end();
        }
        inline const char* get_header_value(const Headers& headers, const std::string& key, size_t id, const char* def) {
            // 可能存在相同的键，返回相同键第一个，以及第一个大于键的迭代器
            auto rng = headers.equal_range(key);
            auto it  = rng.first;
            std::advance(it, static_cast<ssize_t>(id));

            // 如果 it == rng.second就说明，没有这个键
            if (it != rng.second) return it->second.c_str();
            return def;
        }
        inline uint64_t get_header_value_u64(const Headers& headers, const std::string& key, size_t id, uint64_t def) {
            auto rng = headers.equal_range(key);
            auto it  = rng.first;
            std::advance(it, static_cast<ssize_t>(id));

            if (it != rng.second) return std::strtoull(it->second.data(), nullptr, 10);
            return def;
        }
        inline bool has_crlf(const std::string& s) {
            // auto p = s.c_str();
            // while (*p) {
            //     if (*p == '\r' || *p == '\n') return true;
            //     p++;
            // }
            // return false;
            if (s.rfind("\r") != std::string::npos || s.rfind("\n") != std::string::npos) {
                return true;
            }
            return false;
        }
        class ContentProviderAdapter {
        public:
            explicit ContentProviderAdapter(ContentProviderWithoutLength&& content_provider)
                : _content_provider(content_provider) {}
            bool operator() (size_t offset, size_t, DataSink& sink) {
                return _content_provider(offset, sink);
            }
        private:
            ContentProviderWithoutLength _content_provider;
        };

        class SocketStream: public Stream {
        public:
            SocketStream(socket_t sock, time_t read_timeout_sec, time_t read_timeout_usec, 
                time_t write_timeout_sec, time_t write_timeout_usec)
                : _sock(sock)
                , _read_timeout_sec(read_timeout_sec)
                , _read_timeout_usec(read_timeout_usec)
                , _write_timeout_sec(write_timeout_sec)
                , _write_timeout_usec(write_timeout_usec)
                , _read_buf(_read_buf_size, 0) {}
            ~SocketStream() override {};

        public:
            auto is_readable() const -> bool override;
            auto is_writable() const -> bool override;
            auto read(char* ptr, size_t size)        -> ssize_t override;
            auto write(const char* ptr, size_t size) -> ssize_t override;
            auto socket() const -> socket_t override;
            auto get_remote_info(std::string& ip, int& port) const -> void override; 
            auto get_local_info(std::string& ip, int& port)  const -> void override; 

        private:
            socket_t _sock;
            time_t _read_timeout_sec;
            time_t _read_timeout_usec;
            time_t _write_timeout_sec;
            time_t _write_timeout_usec;

            std::vector<char> _read_buf;
            size_t _read_buf_off = 0;
            size_t _read_buf_content_off = 0;

            inline static size_t _read_buf_size = 1024 * 4;
        };
        inline bool is_dir(const std::string& path) {
            struct stat st;
            return stat(path.c_str(), &st) >= 0 && S_ISDIR(st.st_mode);
        }
        inline int shutdown_socket(socket_t sock) {
            return shutdown(sock, SHUT_RDWR);
        }
        inline int close_socket(socket_t sock) {
            return close(sock);
        }

        template <typename BindOrConnect> 
        socket_t create_socket(const std::string& host, const std::string& ip, int port, int address_family, 
                int socket_flags, bool tcp_nodelay, SocketOptions socket_options, BindOrConnect bind_or_connect) {
            const char* node = nullptr;
            struct addrinfo hints;
            struct addrinfo* result;

            memset(&hints, 0, sizeof(addrinfo));
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = 0;

            if (!ip.empty()) {  // 首先检测IP:PORT
                node = ip.c_str();
                hints.ai_family = AF_UNSPEC;
                hints.ai_flags  = AI_NUMERICHOST;
            } else {    // 如果IP为空，再检测Host:PORT
                if (!host.empty()) {
                    node = host.c_str();
                }
                hints.ai_family = address_family;
                hints.ai_flags  = socket_flags;
            }
            if (hints.ai_family == AF_UNIX) {   // 如果协议族是UNIX，则可以直接创建
                const auto addrlen = host.length();
                if (addrlen > sizeof(sockaddr_un::sun_path))
                    return INVALID_SOCKET;
                auto sock = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
                if (sock != INVALID_SOCKET) {
                    sockaddr_un addr{};
                    addr.sun_family = AF_UNIX;
                    std::copy(host.begin(), host.end(), addr.sun_path);

                    hints.ai_addr = reinterpret_cast<sockaddr*>(&addr);
                    hints.ai_addrlen = static_cast<socklen_t>(sizeof(addr) - sizeof(addr.sun_path) + addrlen);

                    fcntl(sock, F_SETFD, FD_CLOEXEC);
                    if (socket_options) 
                        socket_options(sock);
                    if (!bind_or_connect(sock, hints)) { // bind and listen
                        close_socket(sock);
                        sock = INVALID_SOCKET;
                    }
                }
                return sock;
            }
            // 如果不是UNIX，则通过getaddrinfo获取对方地址信息
            auto service = std::to_string(port);
            if (getaddrinfo(node, service.c_str(), &hints, &result)) {
                res_init();
                return INVALID_SOCKET;
            }

            for (auto rp = result; rp; rp = rp->ai_next) {
                auto sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
                if (sock == INVALID_SOCKET)
                    continue;
                if (fcntl(sock, F_SETFD, FD_CLOEXEC) == -1) {
                    close_socket(sock);
                    continue;
                }
                if (tcp_nodelay) {  // 禁用TCP延迟发送
                    auto yes = 1;
                    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const void*>(&yes), sizeof(yes));
                }
                if (socket_options) {
                    socket_options(sock);
                }
                if (rp->ai_family == AF_INET6) {    // 设置INET6协议族，允许IPv4和v6同时处理
                    auto no = 0;
                    setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, reinterpret_cast<const void*>(&no), sizeof(no));
                }
                if (bind_or_connect(sock, *rp)) {
                    freeaddrinfo(result);
                    return sock;
                }
                close_socket(sock);
            }
            freeaddrinfo(result);

            return INVALID_SOCKET;
        }

        template <typename T>
        inline ssize_t handle_eintr(T fn) {
            ssize_t res = 0;
            while (true) {
                res = fn();
                if (res < 0 && errno == EINTR) 
                    continue;
                break;
            }
            return res;
        }

        inline ssize_t select_read(socket_t sock, time_t sec, time_t usec) {
        /* TODO 后续用type trait改写为C++17 */
        #ifdef CPPHTTPLIB_USE_POLL
            struct pollfd pfd_read;
            pfd_read.fd = sock;
            pfd_read.events = POLL_IN;

            auto timeout = static_cast<int>(sec * 1000 + usec / 1000);

            return handle_eintr([&]() {
                return poll(&pfd_read, 1, timeout);
            });
        #endif
            if (sock >= FD_SETSIZE) return 1;

            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(sock, &fds);

            timeval tv;
            tv.tv_sec  = static_cast<long>(sec);
            tv.tv_usec = static_cast<decltype(tv.tv_usec)>(usec);

            return handle_eintr([&]() -> ssize_t { // 当select返回-1且错误为EINTR时不断重试
                return select(static_cast<int>(sock + 1), &fds, nullptr, nullptr, &tv);
            });
        }
        inline bool select_write(socket_t sock, time_t sec, time_t usec) {
        #ifdef CPPHTTPLIB_USE_POLL
            struct pollfd pfd_read;
            pfd_read.fd = sock;
            pfd_read.events = POLL_OUT;

            auto timeout = static_cast<int>(sec * 1000 + usec / 1000);

            return handle_eintr([&]() {
                return poll(&pfd_read, 1, timeout);
            });
        #endif
            if (sock >= FD_SETSIZE) return 1;

            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(sock, &fds);

            timeval tv;
            tv.tv_sec  = static_cast<long>(sec);
            tv.tv_usec = static_cast<decltype(tv.tv_usec)>(usec);

            return handle_eintr([&]() -> ssize_t {
                return select(static_cast<int>(sock + 1), nullptr, &fds, nullptr, &tv);
            });
        }
        inline ssize_t read_socket(socket_t sock, void *ptr, size_t size, int flags) {
            return handle_eintr([&]() -> ssize_t {
                return recv(sock, ptr, size, flags);
            });
        }
        inline bool is_socket_alive(socket_t sock) {
            const auto val = detail::select_read(sock, 0, 0);
            if (val == 0) return true;
            else if (val < 0 && errno == EBADF) return false;
            
            char buf[1];
            return detail::read_socket(sock, &buf[0], sizeof(buf), MSG_PEEK) > 0;
        }
        inline bool keep_alive(socket_t sock, time_t keep_alive_timeout_sec) {
            auto start = std::chrono::steady_clock::now();
            
            while (true) {
                auto val = select_read(sock, 0, 10000);
                if (val < 0) {
                    return false;
                } else if (val == 0) {
                    auto current = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - start);
                    auto timeout = keep_alive_timeout_sec * 1000;
                    if (duration.count() > timeout)
                        return false;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                } else {
                    return true;
                }
            }
        }

        template <typename T>
        inline bool process_server_socket_core(const std::atomic<socket_t> &svr_sock, socket_t sock, size_t keep_alive_max_count,
            time_t keep_alive_timeout_sec, T callback) {
            assert(keep_alive_max_count > 0);

            auto ret = false;
            auto count = keep_alive_max_count;

            while (svr_sock != INVALID_SOCKET && count > 0 && keep_alive(sock, keep_alive_timeout_sec)) {
                auto close_connection = count == 1;
                auto connection_closed = false;

                ret = callback(close_connection, connection_closed);
                if (!ret || connection_closed)
                    break;
                count--;
            }
            return ret;
        }

        template <typename T>
        inline bool process_server_socket(const std::atomic<socket_t>& svr_sock, socket_t sock, size_t keep_alive_max_count, time_t keep_alive_timeout_sec, 
            time_t read_timeout_sec, time_t read_timeout_usec, time_t write_timeout_sec, time_t write_timeout_usec, T callback) {
            return process_server_socket_core(svr_sock, sock, keep_alive_max_count, keep_alive_timeout_sec, 
                [&](bool close_connection, bool& connection_closed) {
                    SocketStream strm(sock, read_timeout_sec, read_timeout_usec, write_timeout_sec, write_timeout_usec);
                    return callback(strm, close_connection, connection_closed);
                });
        }
    } // namespace detail

    namespace detail {
        inline auto SocketStream::is_readable() const -> bool {
            return select_read(_sock, _read_timeout_sec, _read_timeout_usec) > 0;
        }
        inline auto SocketStream::is_writable() const -> bool {
            return select_write(_sock, _write_timeout_sec, _write_timeout_usec) > 0 &&
                is_socket_alive(_sock);
        }
        inline auto SocketStream::read(char *ptr, size_t size) -> ssize_t {
            return {};
        }
        inline auto SocketStream::write(const char *ptr, size_t size) -> ssize_t {
            return {};
        }
        inline auto SocketStream::get_remote_info(std::string &ip, int &port) const -> void {

        }
        inline auto SocketStream::get_local_info(std::string &ip, int &port) const -> void {

        }
        inline auto SocketStream::socket() const -> socket_t{
            return {};
        }
    }

    inline void defaul_socket_options(socket_t sock) {
        int yes = 1;
    #ifdef SO_REUSEPORT
        setsockopt(sock, SOL_SOCKET, SO_REUSEPORT,
             reinterpret_cast<const void *>(&yes), sizeof(yes));
    #else
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
             reinterpret_cast<const void *>(&yes), sizeof(yes));
    #endif
    }
} // namespace httplib

#endif //!__UTIL_H__