#ifndef __SIMPLE_JSON_BUFFER_H__
#define __SIMPLE_JSON_BUFFER_H__

#include "hooks.h"
#include <string>
#include <type_traits>

typedef struct parse_buffer {
    using __self     = parse_buffer*;
    using __self_ref = parse_buffer&;
    std::string content;
    size_t length;
    size_t offset;
    size_t depth;
    internal_hooks hooks;

    parse_buffer();

    EXTERN(__self) skip_utf8_bom();
    EXTERN(__self) skip_whitespace();
} parse_buffer;

template <typename T>
struct is_parse_buffer: std::false_type {};

template <>
struct is_parse_buffer<parse_buffer>: std::true_type {};

template <typename T>
constexpr bool is_parse_buffer_v = is_parse_buffer<T>::value;

template <typename T, typename = std::enable_if_t<is_parse_buffer_v<T>>>
EXTERN(bool) can_read(const T* buffer, size_t size) {
    return (buffer != nullptr) && ((buffer->offset + size) <= buffer->length);
}

template <typename T, typename = std::enable_if_t<is_parse_buffer_v<T>>>
EXTERN(bool) can_access_at_index(const T* buffer, size_t index) {
    return (buffer != nullptr) && ((buffer->offset + index) < buffer->length);
}

template<typename T, typename = std::enable_if_t<is_parse_buffer_v<T>>>
EXTERN(bool) cannot_access_at_index(const T* buffer, size_t index) {
    return !can_access_at_index(buffer, index);
}

template<typename T, typename = std::enable_if_t<is_parse_buffer_v<T>>>
EXTERN(const char*) buffer_at_offset(const T* buffer) {
    return (buffer->content).substr(buffer->offset).c_str();
}

#endif //! __SIMPLE_JSON_BUFFER_H__