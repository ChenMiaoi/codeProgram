#ifndef __SERVER_H__
#define __SERVER_H__

#include "def.hpp"
#include "matcher.hpp"
#include "request.hpp"
#include "response.hpp"
#include "stream.hpp"
#include "task_queue.hpp"
#include "thread_pool.hpp"
#include "data_deal/content.hpp"

#include <atomic>
#include <bits/types/time_t.h>
#include <chrono>
#include <cstddef>
#include <exception>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <sys/socket.h>

namespace httplib {
    class Server {
    public:
        enum class HandlerResponse {
            Handled,
            UnHandled,
        };
        using Handler = std::function<void(const Request&, Response&)>;
        using HandlerWithResponse = std::function<HandlerResponse(const Request&, Response&)>;
        using HandlerWithContentReader = std::function<void(const Request&, Response&, const ContentReader&)>;

        using ExceptionHandler = std::function<void(const Request&, Response&, std::exception_ptr)>;
        using Expect100ContinueHandler = std::function<int(const Request&, Response&)>;
    
    public:
        Server();
        virtual ~Server() = default;
        virtual auto is_valid() const -> bool;
    
    public:
        auto Get (const std::string &pattern, Handler handler) -> Server&;
        auto Post(const std::string &pattern, Handler handler) -> Server&;
        auto Put    (const std::string &pattern, Handler handler) -> Server&;
        auto Patch  (const std::string &pattern, Handler handler) -> Server&;
        auto Delete (const std::string &pattern, Handler handler) -> Server&;
        auto Options(const std::string &pattern, Handler handler) -> Server&;
        auto Put   (const std::string &pattern, HandlerWithContentReader handler) -> Server&;
        auto Post  (const std::string &pattern, HandlerWithContentReader handler) -> Server&;
        auto Patch (const std::string &pattern, HandlerWithContentReader handler) -> Server&;
        auto Delete(const std::string &pattern, HandlerWithContentReader handler) -> Server&;

        auto set_base_dir(const std::string& dir, const std::string& mount_point = {}) -> bool;
        auto set_mount_point(const std::string& mount_point, const std::string& dir, Headers headers = {}) -> bool;
        auto remove_mount_point(const std::string& mount_point) -> bool;

        auto set_file_extension_mimetype_mapping(const std::string& ext, const std::string& mime) -> Server&;
        auto set_default_file_mimetype(const std::string& mime)     -> Server&;
        auto set_error_handler(Handler handler)                     -> Server&;
        auto set_error_handler(HandlerWithResponse handler)         -> Server&;
        auto set_exception_handler(ExceptionHandler handler)        -> Server&;
        auto set_pre_routing_handler(HandlerWithResponse handler)   -> Server&;
        auto set_post_routing_handler(Handler handler)              -> Server&;

        auto set_expect_100_continue_handler(Expect100ContinueHandler handler) -> Server&;
        auto set_logger(Logger logger)                          -> Server&;

        auto set_address_family(int family)                     -> Server&;
        auto set_tcp_nodelay(bool on) -> Server&;
        auto set_socket_options(SocketOptions socket_options)   -> Server&;
        auto set_default_headers(Headers headers)               -> Server&;
        auto set_keep_alive_max_count(size_t count)             -> Server&;
        auto set_keep_alive_timeout(time_t sec)                 -> Server&;
        // TODO 后续改写为C++17 type trait
        auto set_read_timeout(time_t sec, time_t usec = 0)      -> Server&;
        auto set_write_timeout(time_t sec, time_t usec = 0)     -> Server&;
        auto set_idle_interval(time_t sec, time_t usec = 0)     -> Server&;
        auto set_payload_max_length(size_t length)              -> Server&;
        template<typename Rep, typename Period>
        auto set_read_timeout(const std::chrono::duration<Rep, Period>& duration)  -> Server&;
        template<typename Rep, typename Period>
        auto set_write_timeout(const std::chrono::duration<Rep, Period>& duration) -> Server&;  
        template<typename Rep, typename Period>
        auto set_idle_interval(const std::chrono::duration<Rep, Period>& duration) -> Server&; 
        
        auto bind_to_port(const std::string& host, int port, int socket_flags = 0) -> bool;
        auto bind_to_any(const std::string& host, int socket_flags = 0) -> int;
        auto listen(const std::string& host, int port, int socket_flags = 0) -> bool;
        auto listen_after_bind() -> bool;
        auto is_running() const -> bool;
        auto wait_until_ready() const -> void;
        auto stop() -> void;

    protected:
        auto process_request(Stream& strm, bool close_connection, bool& connection_closed, 
            const std::function<void(Request&)>& setup_reqeust) -> bool;

    private:
        using Handlers = 
            std::vector<std::pair<std::unique_ptr<detail::MatcherBase>, Handler>>;
        using HandlersForContentReader = 
            std::vector<std::pair<std::unique_ptr<detail::MatcherBase>, HandlerWithContentReader>>;
        struct MountPointEntry {
            std::string mount_point;
            std::string base_dir;
            Headers headers;
        };

    private:
        auto __make_matcher(const std::string& pattern) -> std::unique_ptr<detail::MatcherBase>;

        // support function
        auto __create_server_socket(const std::string& host, int port, int socket_flags, 
            SocketOptions socket_option) const                                          -> socket_t;
        auto __bind_internal(const std::string& host, int port, int socket_flags)       -> int;
        auto __listen_internal() -> bool;
        auto __routing(Request& req, Response& res, Stream& strm) -> bool;
        auto __handle_file_request(const Request& req, Response& res, bool head = false) -> bool;
        auto __dispatch_request(Request& req, Response& res, const Handlers& handlers)  -> bool;
        auto __dispatch_request_content_reader(Request& req, Response& res, 
            ContentReader content_reader, const HandlersForContentReader& handlers)     -> bool;
        auto __parse_request_line(const char* s, Request& req)                          -> bool;
        auto __apply_ranges(const Request& req, Response& res, 
            std::string& content_type, std::string& boundary)                           -> void;
        auto __write_response(Stream& strm, bool close_connection, 
                        const Request& req, Response& res)                              -> bool;
        auto __write_response_with_content(Stream& strm, bool close_connection, 
                        const Request& req, Response& res)                              -> bool;
        auto __write_response_core(Stream& strm, bool close_connection, 
                        const Request& req, Response& res, bool need_apply_ranges)      -> bool;
        auto __write_content_with_provider(Stream& strm, const Request& req, Response& res, 
                        const std::string& boundary, const std::string& content_type)   -> bool;
        auto __read_content(Stream &strm, Request &req, Response &res)                  -> bool;
        auto __read_content_with_content_receiver(Stream &strm, Request &req, Response &res, 
                        ContentRecevier receiver, MultipartContentHeader multipart_header, 
                        ContentRecevier multipart_receiver)                             -> bool;
        auto __read_content_core(Stream &strm, Request &req, Response &res, 
                        ContentRecevier receiver, MultipartContentHeader multipart_header,
                        ContentRecevier multipart_receiver)                             -> bool;
        auto virtual __process_close_socket(socket_t sock)                              -> bool;

    protected:
        std::atomic<socket_t> _svr_sock {INVALID_SOCKET};
        size_t _payload_max_length     = CPPHTTPLIB_PAYLOAD_MAX_LENGTH;

        size_t _keep_alive_max_count   = CPPHTTPLIB_KEEPALIVE_MAX_COUNT;
        time_t _keep_alive_timeout_sec = CPPHTTPLIB_KEEPALIVE_TIMEOUT_SECOND;
        time_t _read_timeout_sec       = CPPHTTPLIB_READ_TIMEOUT_SECOND;
        time_t _read_timeout_usec      = CPPHTTPLIB_READ_TIMEOUT_USECOND;
        time_t _write_timeout_sec      = CPPHTTPLIB_WRITE_TIMEOUT_SECOND;
        time_t _write_timeout_usec     = CPPHTTPLIB_WRITE_TIMEOUT_USECOND;
        time_t _idle_interval_sec      = CPPHTTPLIB_IDLE_INTERVAL_SECOND;
        time_t _idle_interval_usec     = CPPHTTPLIB_IDLE_INTERVAL_USECOND;

    private:
        int _address_family = AF_UNSPEC;
        bool _tcp_nodelay = CPPHTTPLIB_TCP_NODELAY;
        std::atomic<bool> _is_running {false};
        std::atomic<bool> _done {false};
        std::vector<MountPointEntry> _base_dirs;
        std::string _default_file_mimetype = "application/octet-stream";
        std::map<std::string, std::string> _file_extension_mimetype;
        std::function<TaskQueue*(void)> _new_stack_queue;

        Handlers _file_request_handlers;
        Handlers _get_handlers;
        Handlers _post_handlers;
        Handlers _put_handlers;
        Handlers _patch_handlers;
        Handlers _delete_handlers;
        Handlers _options_handlers;

        Headers _default_headers;

        HandlersForContentReader _post_for_content_reader;
        HandlersForContentReader _put_for_content_reader;
        HandlersForContentReader _patch_for_content_reader;
        HandlersForContentReader _delete_for_content_reader;

        Handler _post_routing_handler;
        ExceptionHandler _exception_handler;
        HandlerWithResponse _error_handler;
        HandlerWithResponse _pre_routing_handler;
        Expect100ContinueHandler _expect_continue_handler;

        Logger _logger;
        SocketOptions _socket_options = defaul_socket_options;
    };
}

#endif //! __SERVER_H__
