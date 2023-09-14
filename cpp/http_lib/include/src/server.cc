#include "../server.hpp"
#include "def.hpp"
#include <atomic>
#include <cassert>

namespace httplib {
    Server::Server(): _new_stack_queue([]() -> TaskQueue* {
        return new ThreadPool(CPPHTTPLIB_THREAD_POOL_COUNT);
    }) {}
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
    auto Server::__make_matcher(const std::string& pattern) -> std::unique_ptr<detail::MatcherBase> {
        if (pattern.find("/:") != std::string::npos) {
            std::cout << "[Debug]: " << "entry the make_matcher, PathParamsMatcher" << std::endl;
            return std::make_unique<detail::PathParamsMatcher>(pattern);
        }
        std::cout << "[Debug]: " << "entry the make_matcher, RegexMatcher" << std::endl;
        return std::make_unique<detail::RegexMatcher>(pattern);
    }
    auto Server::__bind_internal(const std::string& host, int port, int socket_flags) -> int {
        return {};
    }
    auto Server::__listen_internal() -> bool {
        return {};
    }
}