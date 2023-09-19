#include "../server.hpp"
#include "def.hpp"
#include "detail.hpp"
#include "stream.hpp"
#include "task_queue.hpp"
#include "util.hpp"
#include <asm-generic/errno-base.h>
#include <asm-generic/socket.h>
#include <atomic>
#include <bits/types/struct_timeval.h>
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cstddef>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>

namespace httplib {
    Server::Server(): _new_stack_queue([]() -> TaskQueue* {
        return new ThreadPool(CPPHTTPLIB_THREAD_POOL_COUNT);
    }) {}
    auto Server::is_valid() const -> bool {
        return true;
    }
    auto Server::Get(const std::string &pattern, Handler handler) -> Server& {
        std::cout << "[Debug]: " << "entry the Get, pattern: " << pattern << std::endl;
        _get_handlers.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        
        return *this;
    }
    auto Server::Post(const std::string& pattern, Handler handler) -> Server& {
        _post_handlers.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Put(const std::string& pattern, Handler handler) -> Server& {
        _put_handlers.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Patch(const std::string& pattern, Handler handler) -> Server& {
        _patch_handlers.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Delete(const std::string& pattern, Handler handler) -> Server& {
        _delete_handlers.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Options(const std::string &pattern, Handler handler) -> Server& {
        _options_handlers.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Post(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _post_for_content_reader.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Put(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _put_for_content_reader.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Patch(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _patch_for_content_reader.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Delete(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _delete_for_content_reader.push_back(
            std::make_pair(__make_matcher(pattern), std::move(handler)));
        return *this;
    }

    auto Server::set_base_dir(const std::string &dir, const std::string& mount_point) -> bool {
        return set_mount_point(mount_point, dir);
    }
    auto Server::set_mount_point(const std::string &mount_point, const std::string &dir, Headers headers) -> bool {
        if (detail::is_dir(dir)) {
            std::string mnt = !mount_point.empty() ? mount_point : "/";
            if (!mnt.empty() && mnt[0] == '/') {
                _base_dirs.push_back({mnt, dir, std::move(headers)});
                return true;
            }
        }
        return false;
    }
    auto Server::remove_mount_point(const std::string &mount_point) -> bool {
        for (auto it = _base_dirs.begin(); it != _base_dirs.end(); ++it) {
            if (it->mount_point == mount_point) {
                _base_dirs.erase(it);
                return true;
            }
        }
        return false;
    }
    auto Server::set_file_extension_mimetype_mapping(const std::string &ext, const std::string &mime) -> Server& {
        _file_extension_mimetype[ext] = mime;
        return *this;
    }
    auto Server::set_default_file_mimetype(const std::string &mime) -> Server& {
        _default_file_mimetype = mime;
        return *this;
    }
    auto Server::set_exception_handler(ExceptionHandler handler) -> Server& {
        _exception_handler = std::move(handler);
        return *this;
    }
    auto Server::set_error_handler(Handler handler) -> Server& {
        _error_handler = [handler](const Request& req, Response& res) {
            handler(req, res);
            return HandlerResponse::Handled;
        };
        return *this;
    }
    auto Server::set_error_handler(HandlerWithResponse handler) -> Server& {
        _error_handler = std::move(handler);
        return *this;
    }
    auto Server::set_pre_routing_handler(HandlerWithResponse handler) -> Server& {
        _pre_routing_handler = std::move(handler);
        return *this;
    }
    auto Server::set_post_routing_handler(Handler handler) -> Server& {
        _post_routing_handler = std::move(handler);
        return *this;
    }
    auto Server::set_logger(Logger logger) -> Server& {
        _logger = std::move(logger);
        return *this;
    }
    auto Server::set_expect_100_continue_handler(Expect100ContinueHandler handler) -> Server& {
        _expect_continue_handler = std::move(handler);
        return *this;
    }
    auto Server::set_address_family(int family) -> Server& {
        _address_family = family;
        return *this;
    }
    auto Server::set_tcp_nodelay(bool on) -> Server& {
        _tcp_nodelay = on;
        return *this;
    }
    auto Server::set_socket_options(SocketOptions socket_options) -> Server& {
        _socket_options = std::move(socket_options);
        return *this;
    }
    auto Server::set_default_headers(Headers headers) -> Server& {
        _default_headers = std::move(headers);
        return *this;
    }
    auto Server::set_keep_alive_max_count(size_t count) -> Server& {
        _keep_alive_max_count = count;
        return *this;
    }
    auto Server::set_keep_alive_timeout(time_t sec) -> Server& {
        _keep_alive_timeout_sec = sec;
        return *this;
    }
    auto Server::set_read_timeout(time_t sec, time_t usec) -> Server& {
        _read_timeout_sec = sec, _read_timeout_usec = usec;
        return *this;
    }
    auto Server::set_write_timeout(time_t sec, time_t usec) -> Server& {
        _write_timeout_sec = sec, _write_timeout_usec = usec;
        return *this;
    }
    auto Server::set_idle_interval(time_t sec, time_t usec) -> Server& {
        _idle_interval_sec = sec, _idle_interval_usec = usec;
        return *this;
    }
    auto Server::set_payload_max_length(size_t length) -> Server& {
        _payload_max_length = length;
        return *this;
    }

    auto Server::bind_to_port(const std::string &host, int port, int socket_flags) -> bool {
        if (__bind_internal(host, port, socket_flags) < 0) 
            return false;
        return true;
    }
    auto Server::bind_to_any(const std::string &host, int socket_flags) -> int {
        return __bind_internal(host, 0, socket_flags);
    }
    auto Server::listen_after_bind() -> bool {
        auto se = detail::scope_exit([&]() { _done = true; });
        return __listen_internal();
    }
    auto Server::listen(const std::string &host, int port, int socket_flags) -> bool {
        auto se = detail::scope_exit([&]() { _done = true; });
        return bind_to_port(host, port, socket_flags) && __listen_internal();
    }
    auto Server::is_running() const -> bool {
        return _is_running;
    }
    auto Server::wait_until_ready() const -> void {
        while (!is_running() && !_done) {
            std::this_thread::sleep_for(std::chrono::milliseconds {1});
        }
    }
    auto Server::stop() -> void {
        if (_is_running) {
            assert(_svr_sock != INVALID_SOCKET);
            std::atomic<socket_t> sock (_svr_sock.exchange(INVALID_SOCKET));
            detail::shutdown_socket(sock);
            detail::close_socket(sock);
        }
    }
}

/* for support private */
namespace httplib {
    auto Server::process_request(Stream& strm, bool close_connection, bool& connection_closed, 
            const std::function<void(Request&)>& setup_reqeust) -> bool {
        return {};
    }
    auto Server::__make_matcher(const std::string& pattern) -> std::unique_ptr<detail::MatcherBase> {
        if (pattern.find("/:") != std::string::npos) {
            std::cout << "[Debug]: " << "entry the make_matcher, PathParamsMatcher" << std::endl;
            return std::make_unique<detail::PathParamsMatcher>(pattern);
        }
        std::cout << "[Debug]: " << "entry the make_matcher, RegexMatcher" << std::endl;
        return std::make_unique<detail::RegexMatcher>(pattern);
    }
    auto Server::__create_server_socket(const std::string& host, int port, int socket_flags, 
        SocketOptions socket_option) const -> socket_t {
        return detail::create_socket(host, {}, port, _address_family, socket_flags, _tcp_nodelay, 
            std::move(_socket_options), [](socket_t sock, struct addrinfo& ai) -> bool {
                if (::bind(sock, ai.ai_addr, static_cast<socklen_t>(ai.ai_addrlen)))
                    return false;
                if (::listen(sock, CPPHTTPLIB_LISTEN_BACKLOG))
                    return false;
                return true;
            });
    }
    auto Server::__bind_internal(const std::string& host, int port, int socket_flags) -> int {
        if (!is_valid()) return -1;

        _svr_sock = __create_server_socket(host, port, socket_flags, _socket_options);
        if (_svr_sock == INVALID_SOCKET) 
            return -1;

        if (port == 0) {
            struct sockaddr_storage addr;
            socklen_t addr_len = sizeof addr;
            if (getsockname(_svr_sock, reinterpret_cast<struct sockaddr*>(&addr), &addr_len) == -1)
                return -1;
            if (addr.ss_family == AF_INET) 
                return ntohs(reinterpret_cast<struct sockaddr_in*>(&addr)->sin_port);
            else if (addr.ss_family == AF_INET6) 
                return ntohs(reinterpret_cast<struct sockaddr_in6*>(&addr)->sin6_port);
            else 
                return -1;
        } else {
            return port;
        }
    }
    auto Server::__listen_internal() -> bool {
        auto ret = true;
        _is_running = true;

        auto se = detail::scope_exit([&]() { _is_running = false; });
        {
            std::unique_ptr<TaskQueue> task_queue(_new_stack_queue());
            while (_svr_sock != INVALID_SOCKET) {
                if (_idle_interval_sec > 0 || _idle_interval_usec > 0) {
                    auto val = detail::select_read(_svr_sock, _idle_interval_sec, _idle_interval_usec);
                    if(val == 0) {
                        task_queue->on_idle();
                        continue;
                    }
                }
                socket_t sock = accept(_svr_sock, nullptr, nullptr);
                if (sock == INVALID_SOCKET) {
                    if (errno == EMFILE) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        continue;
                    } else if (errno == EINTR || errno == EAGAIN) {
                        continue;
                    }
                    if (_svr_sock != INVALID_SOCKET) {
                        detail::close_socket(_svr_sock);
                        ret = false;
                    } else { // 服务器的socket由用户关闭 
                    
                    }
                    break;
                }
                {
                    timeval tv;
                    tv.tv_sec  = static_cast<long>(_read_timeout_sec);
                    tv.tv_usec = static_cast<decltype(tv.tv_usec)>(_read_timeout_usec);
                    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const void*>(&tv), sizeof(tv));
                }
                {
                    timeval tv;
                    tv.tv_sec  = static_cast<long>(_write_timeout_sec);
                    tv.tv_usec = static_cast<decltype(tv.tv_usec)>(_write_timeout_usec);
                    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const void*>(&tv), sizeof(tv));
                }
                task_queue->enqueue([this, sock]() { __process_close_socket(sock); });
            }
            task_queue->shutdown();
        }
        return ret;
    }

    auto Server::__process_close_socket(socket_t sock) -> bool {
        auto ret = detail::process_server_socket(_svr_sock, sock, _keep_alive_max_count, _keep_alive_timeout_sec, 
            _read_timeout_sec, _read_timeout_usec, _write_timeout_sec, _write_timeout_usec, 
            [this](Stream& strm, bool close_connection, bool& connection_closed) {
                return process_request(strm, close_connection, connection_closed, nullptr);
            });

        detail::shutdown_socket(sock);
        detail::close_socket(sock);
        return ret;
    }
}