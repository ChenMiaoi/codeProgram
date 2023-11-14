#include "include/json.h"
#include <ctype.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <type_traits>

internal_hooks global_hooks;

EXTERN(const std::string) simple_json::version(void) {
    static std::ostringstream oos;
    oos << "version "
        << SIMPLE_JSON_VERSION_MAJOR << "." 
        << SIMPLE_JSON_VERSION_MINOR << "." 
        << SIMPLE_JSON_VERSION_PATCH;
    info << "version function success!";
    return oos.str();
}

EXTERN(simple_json*) simple_json::parse(const std::string& value) {
    info << "test parse";
    parse_with_opts(value, nullptr, false);
    return {};
}

EXTERN(simple_json*) simple_json::parse_with_length(const std::string& value, size_t len) {
    parse_with_len_opts(value, len, nullptr, false);
    return {};
}

EXTERN(simple_json*) simple_json::parse_with_opts(const std::string& value, 
        const char** return_parse_end, bool require_null_terminated) {
    info << "test parse_with_opts";
    size_t buffer_length;
    if (value.empty()) return nullptr;

    buffer_length = value.length() + sizeof("");
    return parse_with_len_opts(value, buffer_length, return_parse_end, require_null_terminated);
}

EXTERN(simple_json*) simple_json::parse_with_len_opts(const std::string& value, size_t len, 
        const char** return_parse_end, bool require_null_terminated) {
    simple_json* item = nullptr;    

    if (value.empty() || len == 0) goto fail;

    buffer.content = value;
    buffer.length  = len;
    buffer.offset  = 0;
    buffer.hooks   = global_hooks;

    if ((item = new_item()) == nullptr) goto fail;

    if (!parse_value(item, buffer.skip_utf8_bom()->skip_whitespace())) 
        goto fail;
    return {};
fail:
    return {};
}

/**
 * @brief create a return node
 */
EXTERN(simple_json*) simple_json::new_item() {
    simple_json* node = (simple_json*)global_hooks._allocate(sizeof(simple_json));
    if (node)
        memset(node, '\0', sizeof(simple_json));
    return node;
}

/**
 * @brief to parse the value and analyze the respective types
 * @note We need to note that after analyzing the type, the offset 
 * needs to be increased by different values depending on the type
 * @param item the json item node
 * @param input_buffer user input json buffer, we need parse it
 */
EXTERN(bool) simple_json::parse_value(simple_json* const item, parse_buffer* const input_buffer) {
    if (input_buffer == nullptr || input_buffer->content.empty()) return false;

    if (can_read(input_buffer, 4) && 
        (strncmp((const char*)buffer_at_offset(input_buffer), "null", 4) == 0)) {
        item->type = SIMPLE_JSON_NULL;
        input_buffer->offset += 4;      // ? because null is 4-bit character
        info << "success check the 'null', now offset = " << input_buffer->offset;
        return true;
    }
    if (can_read(input_buffer, 5) && 
        (strncmp((const char*)buffer_at_offset(input_buffer), "false", 5) == 0)) {
        item->type = SIMPLE_JSON_FALSE;
        input_buffer->offset += 5;      // ? because false is 5-bit character
        info << "success check the 'false', now offset = " << input_buffer->offset;

        return true;
    }
    if (can_read(input_buffer, 4) && 
        (strncmp((const char*)buffer_at_offset(input_buffer), "true", 4) == 0)) {
        item->type = SIMPLE_JSON_TRUE;
        input_buffer->offset += 4;      // ? because true is 4-bit character
        info << "success check the 'true', now offset = " << input_buffer->offset;
        return true;
    }
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '\"'))
        return parse_string();
    if (can_access_at_index(input_buffer, 0) && 
        (buffer_at_offset(input_buffer)[0] == '-') || isdigit((buffer_at_offset(input_buffer)[0])))
        return parse_number();
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '['))
        return parse_array();
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '{'))
        return parse_object();

    return false;
}

EXTERN(bool) simple_json::parse_string() {
    // TODO 
    return {};
}
EXTERN(bool) simple_json::parse_number() {
    // TODO 
    return {};
}
EXTERN(bool) simple_json::parse_array() {
    // TODO 
    return {};
}
EXTERN(bool) simple_json::parse_object() {
    // TODO 
    return {};
}

EXTERN(void) simple_json_hooks::from() {
    global_hooks._allocate = malloc;
    if (_malloc_fn != nullptr) {
        global_hooks._allocate = _malloc_fn;
    }
    global_hooks._deallocate = free;
    if (_free_fn != nullptr) {
        global_hooks._deallocate = _free_fn;
    }
    global_hooks._reallocate = nullptr;
    if (std::is_same_v<decltype(global_hooks._allocate), decltype(malloc)>
        && std::is_same_v<decltype(global_hooks._deallocate), decltype(free)>) {
        global_hooks._reallocate = realloc;
    }
}