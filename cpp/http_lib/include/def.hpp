#ifndef __DEF_H__
#define __DEF_H__

#include "detail.hpp"

#include <cstdint>
#include <functional>
#include <regex>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <sys/types.h>
#include <utility>
#include <vector>

#ifndef CPPHTTPLIB_REDIRECT_MAX_COUNT
#define CPPHTTPLIB_REDIRECT_MAX_COUNT 20
#endif

namespace httplib {
    struct Response;

    using Headers   = std::multimap<std::string, std::string, detail::ci>;
    using Params    = std::multimap<std::string, std::string>;
    using Match     = std::smatch;
    using Progress  = std::function<bool(uint64_t current, uint64_t total)>;
    using ResponseHeadler = std::function<bool(const Response& response)>;

    using Range  = std::pair<ssize_t, ssize_t>;
    using Ranges = std::vector<Range>;

    using socket_t = int;
    using Logger = std::function<void(const Response&, const Response&)>;
    using SocketOtions = std::function<void(socket_t sock)>;
}

#endif //!__DEF_H__