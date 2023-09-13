#include "../server.hpp"

namespace httplib {
    Server::Server(): _new_stack_queue([]() -> TaskQueue* {
        return new ThreadPool(CPPHTTPLIB_THREAD_POOL_COUNT);
    }) {}
    auto Server::make_matcher(const std::string& pattern) -> std::unique_ptr<detail::MatcherBase> {
        if (pattern.find("/:") != std::string::npos) {
            std::cout << "[Debug]: " << "entry the make_matcher, PathParamsMatcher" << std::endl;
            return std::make_unique<detail::PathParamsMatcher>(pattern);
        }
        std::cout << "[Debug]: " << "entry the make_matcher, RegexMatcher" << std::endl;
        return std::make_unique<detail::RegexMatcher>(pattern);
    }
    auto Server::Get(const std::string &pattern, Handler handler) -> Server& {
        std::cout << "[Debug]: " << "entry the Get, pattern: " << pattern << std::endl;
        _get_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        
        return *this;
    }
    auto Server::Post(const std::string& pattern, Handler handler) -> Server& {
        _post_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Put(const std::string& pattern, Handler handler) -> Server& {
        _put_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Patch(const std::string& pattern, Handler handler) -> Server& {
        _patch_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Delete(const std::string& pattern, Handler handler) -> Server& {
        _delete_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Options(const std::string &pattern, Handler handler) -> Server& {
        _options_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Post(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _post_for_content_reader.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Put(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _put_for_content_reader.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Patch(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _patch_for_content_reader.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
    auto Server::Delete(const std::string& pattern, HandlerWithContentReader handler) -> Server& {
        _delete_for_content_reader.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
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
}