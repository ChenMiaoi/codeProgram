#include "../server.hpp"
#include <memory>
#include <utility>

namespace httplib {
    Server::Server(): _new_stack_queue([]() -> TaskQueue* {
        return new ThreadPool(CPPHTTPLIB_THREAD_POOL_COUNT);
    }) {}
    auto Server::make_matcher(const std::string& pattern) -> std::unique_ptr<detail::MatcherBase> {
        if (pattern.find("/:") != std::string::npos)
            return std::make_unique<detail::PathParamsMatcher>(pattern);
        return std::make_unique<detail::RegexMatcher>(pattern);
    }
    auto Server::Get(const std::string &pattern, Handler handler) -> Server& {
        _get_handlers.push_back(
            std::make_pair(make_matcher(pattern), std::move(handler)));
        return *this;
    }
}