#ifndef __DEF_H__
#define __DEF_H__

#include "detail.hpp"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <regex>
#include <string>
#include <limits>
#include <map>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <sys/types.h>
#include <utility>
#include <vector>

const int INVALID_SOCKET = -1;
const size_t CPPHTTPLIB_PAYLOAD_MAX_LENGTH         = 
            std::numeric_limits<size_t>::max();
const bool CPPHTTPLIB_TCP_NODELAY                  = false;

const size_t CPPHTTPLIB_READ_TIMEOUT_SECOND        = 5;
const size_t CPPHTTPLIB_READ_TIMEOUT_USECOND       = 0;
const size_t CPPHTTPLIB_WRITE_TIMEOUT_SECOND       = 5;
const size_t CPPHTTPLIB_WRITE_TIMEOUT_USECOND      = 0;

const size_t CPPHTTPLIB_IDLE_INTERVAL_SECOND       = 0;
const size_t CPPHTTPLIB_IDLE_INTERVAL_USECOND      = 0;

const size_t CPPHTTPLIB_REDIRECT_MAX_COUNT         = 20;
const size_t CPPHTTPLIB_KEEPALIVE_MAX_COUNT        = 2;
const size_t CPPHTTPLIB_KEEPALIVE_TIMEOUT_SECOND   = 5;

const int CPPHTTPLIB_THREAD_POOL_COUNT             = 
    ((std::max)(8u, std::thread::hardware_concurrency() > 0  
                            ? std::thread::hardware_concurrency() - 1 
                            : 0));

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
    using SocketOptions = std::function<void(socket_t sock)>;
}

#endif //!__DEF_H__