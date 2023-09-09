#ifndef __UTIL_H__
#define __UTIL_H__

#include "def.hpp"
#include <cstddef>
#include <iterator>
#include <string>
#include <sys/types.h>

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
    }
}

#endif //!__UTIL_H__