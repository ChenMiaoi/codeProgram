#ifndef __UTIL_H__
#define __UTIL_H__

#include "def.hpp"
#include "data_deal/data_sink.hpp"

#include <algorithm>
#include <asm-generic/errno-base.h>
#include <asm-generic/socket.h>
#include <atomic>
#include <bits/types/struct_timeval.h>
#include <bits/types/time_t.h>
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

            return handle_eintr([&]() { // 当select返回-1且错误为EINTR时不断重试
                return select(static_cast<int>(sock + 1), &fds, nullptr, nullptr, &tv);
            });
        }

        template <typename T>
        inline bool process_server_socket_core(const std::atomic<socket_t> &svr_sock, socket_t sock, size_t keep_alive_max_count,
            time_t keep_alive_timeout_sec, T callback) {
            /* TODO */
            return {};
        }

        template <typename T>
        inline bool process_server_socket(const std::atomic<socket_t>& svr_sock, socket_t sock, size_t keep_alive_max_count, time_t keep_alive_timeout_sec, 
            time_t read_timeout_sec, time_t read_timeout_usec, time_t write_timeout_sec, time_t write_timeout_usec, T callback) {
            /* TODO */
            return {};
        }
    } // namespace detail

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