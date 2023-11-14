#ifndef __JSON_H__
#define __JSON_H__

#include "defs.h"
#include "hooks.h"
#include "error.h"
#include "buffer.h"

#include <functional>
#include <string>
#include <type_traits>

#include <cstring>

typedef class simple_json {
    using __self = simple_json*;

    __self next;
    __self prev;
    __self child;
    int     type;
    char*   valuestring;
    int     valueint;
    double  valuedouble;
    char*   string;

    parse_buffer buffer;
    error global_error;
public:
    EXTERN(const std::string) version(void);
    EXTERN(__self) parse(const std::string& value);
    EXTERN(__self) parse_with_length(const std::string& value, size_t len);
    EXTERN(__self) parse_with_opts(const std::string& value, 
        const char** return_parse_end, bool require_null_terminated);
    EXTERN(__self) parse_with_len_opts(const std::string& value, size_t len, 
        const char** return_parse_end, bool require_null_terminated);
    
    EXTERN(__self) new_item();
    EXTERN(bool) parse_value(__self const item, parse_buffer* const input_buffer);
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

#endif //! __JSON_H__