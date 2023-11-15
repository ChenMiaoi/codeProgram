#ifndef __JSON_H__
#define __JSON_H__

#include "defs.h"
#include "hooks.h"
#include "error.h"
#include "buffer.h"

#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>

#include <cstring>
#include <variant>

typedef class simple_json {
    using __self = simple_json*;

    __self next;
    __self prev;
    __self child;
    int     type;
    // char*   valuestring;
    // int     valueint;
    // double  valuedouble;
    char*   string;

    parse_buffer buffer;
    error global_error;
public:
    std::variant<int, double, bool, std::string> value;

    template <int Type>
    constexpr auto __get_content() const;
    constexpr auto get_content() const;

    friend std::ostream& operator<< (std::ostream& _cout, const simple_json& json);
    void print_value(std::ostream& os) const;
protected:
    EXTERN(__self) new_item();

    EXTERN(bool) parse_value(__self const item, parse_buffer* const input_buffer);
    EXTERN(bool) parse_string(__self const item, parse_buffer* const input_buffer);
    EXTERN(bool) parse_number();
    EXTERN(bool) parse_array();
    EXTERN(bool) parse_object();
public:
    EXTERN(const std::string) version(void);
    EXTERN(__self) parse(const std::string& value);
    EXTERN(__self) parse_with_length(const std::string& value, size_t len);
    EXTERN(__self) parse_with_opts(const std::string& value, 
        const char** return_parse_end, bool require_null_terminated);
    EXTERN(__self) parse_with_len_opts(const std::string& value, size_t len, 
        const char** return_parse_end, bool require_null_terminated);
} simple_json;

typedef class simple_json_hooks {
    using __self = simple_json_hooks*;
    using MallocFn  = std::function<SIMPLE_JSON_CDECL void*(size_t)>;
    using FreeFn    = std::function<SIMPLE_JSON_CDECL void*(void*)>;

    MallocFn _malloc_fn;
    FreeFn   _free_fn;
public:
    EXTERN(void) from();
} simple_json_hooks;

template <int Type>
constexpr auto simple_json::__get_content() const {
    if constexpr (Type == SIMPLE_JSON_NULL) {
        // return std::make_tuple("json_int", std::get<int>(value));
    } else if constexpr (Type == SIMPLE_JSON_FALSE) {
        // return std::make_tuple("json_bool", std::get<bool>(value));
    } else if constexpr (Type == SIMPLE_JSON_TRUE) {
        // return std::make_tuple("json_bool", std::get<bool>(value));
    } else if constexpr (Type == SIMPLE_JSON_STRING) {
        // return std::make_tuple("json_string", std::get<std::string>(value));
    }
}

constexpr auto simple_json::get_content() const {
    if (type == SIMPLE_JSON_NULL) {
        return __get_content<SIMPLE_JSON_NULL>();
    } else if (type == SIMPLE_JSON_FALSE) {
        return __get_content<SIMPLE_JSON_FALSE>();
    } else if (type == SIMPLE_JSON_TRUE) {
        return __get_content<SIMPLE_JSON_TRUE>();
    } else if (type == SIMPLE_JSON_STRING) {
        return __get_content<SIMPLE_JSON_STRING>();
    }
}

#endif //! __JSON_H__