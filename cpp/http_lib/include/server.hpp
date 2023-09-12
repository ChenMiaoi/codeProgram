#ifndef __SERVER_H__
#define __SERVER_H__

#include "def.hpp"
#include "matcher.hpp"
#include "request.hpp"
#include "response.hpp"
#include "data_deal/content.hpp"
#include "task_queue.hpp"
#include "thread_pool.hpp"

#include <atomic>
#include <bits/types/time_t.h>
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

    private:
        auto make_matcher(const std::string& pattern) -> std::unique_ptr<detail::MatcherBase>;

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
        int _address_family = AF_UNSPEC;
        bool _tcp_nodelay = CPPHTTPLIB_TCP_NODELAY;
        std::atomic<bool> _is_running {false};
        std::atomic<bool> _done {false};
        std::vector<MountPointEntry> _base_dirs;
        std::map<std::string, std::string> _file_extension_mimetype;
        std::function<TaskQueue*(void)> _new_stack_queue;

        Handlers _file_request_handlers;
        Handlers _get_handlers;
        Handlers _post_handlers;
        Handlers _put_handlers;
        Handlers _patch_handlers;
        Handlers _delete_handlers;
        Handlers _options_handlers;
        Handlers _default_headers;

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
