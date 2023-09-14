#ifndef __UTIL_H__
#define __UTIL_H__

#include "def.hpp"
#include "data_deal/data_sink.hpp"

#include <asm-generic/socket.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <string>
#include <sys/socket.h>
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