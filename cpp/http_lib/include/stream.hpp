#ifndef __STREAM_H__
#define __STREAM_H__

#include "def.hpp"
#include <cstddef>
#include <sys/types.h>

namespace httplib {
    class Stream {
    public:
        virtual ~Stream() = default;

        virtual auto is_readable() const -> bool = 0;
        virtual auto is_writable() const -> bool = 0;

        virtual auto read(char* ptr, size_t size)        -> ssize_t = 0;
        virtual auto write(const char* ptr, size_t size) -> ssize_t = 0;
        virtual socket_t socket() const = 0;
        virtual auto get_remote_info(std::string& ip, int& port) const -> void = 0;
        virtual auto get_local_info (std::string& ip, int& port) const -> void = 0;

        template <typename ... Args>
        ssize_t write_format(const char* fmt, const Args& ... args);

        ssize_t write(const char* ptr);
        ssize_t write(const std::string& s);
    };
}

#endif //!__STREAM_H__