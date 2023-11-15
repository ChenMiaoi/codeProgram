#include "include/json.h"
#include <ctype.h>
#include <ostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <tuple>
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
    return parse_with_opts(value, nullptr, false);
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
    return item;
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
        !buffer_at_offset(input_buffer).compare(0, 4, "null")) {
        // (strncmp((const char*)buffer_at_offset(input_buffer), "null", 4) == 0)) {
        item->type = SIMPLE_JSON_NULL;
        input_buffer->offset += 4;      // ? because null is 4-bit character
        info << "success check the 'null', now offset = " << input_buffer->offset;
        return true;
    }
    if (can_read(input_buffer, 5) && 
        !buffer_at_offset(input_buffer).compare(0, 5, "false")) {
        // (strncmp((const char*)buffer_at_offset(input_buffer), "false", 5) == 0)) {
        item->type = SIMPLE_JSON_FALSE;
        input_buffer->offset += 5;      // ? because false is 5-bit character
        info << "success check the 'false', now offset = " << input_buffer->offset;

        return true;
    }
    if (can_read(input_buffer, 4) && 
        !buffer_at_offset(input_buffer).compare(0, 4, "true")) {
        // (strncmp((const char*)buffer_at_offset(input_buffer), "true", 4) == 0)) {
        item->type = SIMPLE_JSON_TRUE;
        input_buffer->offset += 4;      // ? because true is 4-bit character
        info << "success check the 'true', now offset = " << input_buffer->offset;
        return true;
    }
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '\"'))
        return parse_string(item, input_buffer);
    if (can_access_at_index(input_buffer, 0) && 
        (buffer_at_offset(input_buffer)[0] == '-') || isdigit((buffer_at_offset(input_buffer)[0])))
        return parse_number();
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '['))
        return parse_array();
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '{'))
        return parse_object();

    return false;
}

int utf16_literal_to_utf8 () {
    // TODO
    return {};
}

/**
 * @brief parse string type for json
 * ! @note fix bug
 */
EXTERN(bool) simple_json::parse_string(simple_json* const item, parse_buffer* const input_buffer) {
    // TODO 
    info << "entry parse_string";
    //? Skip the characters that have already been read, starting at the unread place
    std::string input_string = buffer_at_offset(input_buffer);
    auto input_pointor = input_string.begin() + 1;
    auto input_end = input_string.end();
    char* output_pointer = NULL, *output = NULL;

    //? detects whether it begins with `"`
    if (buffer_at_offset(input_buffer)[0] != '\"') goto fail;
    {
        size_t allocation_len = 0, skipped_bytes = 0;
        //! detects all characters from `"` to `"`
        while (input_pointor != input_end && (*input_pointor != '\"')) {
            //? The escape character will only be treated as a character
            //? so after detection, it needs to be skipped +1
            if (*input_pointor == '\\') {
                if (input_end - input_pointor < 0) goto fail;
                skipped_bytes++, input_pointor++;
            }
            input_pointor++;
        }
        if (input_pointor - input_end > 0 || *input_pointor != '\"') goto fail;

        //! allocate memory for string
        allocation_len = input_end - input_string.begin() + skipped_bytes;
        output = (char*)input_buffer->hooks._allocate(allocation_len + sizeof(""));
        if (output == nullptr) goto fail;
    }

    output_pointer = output;
    input_pointor = input_string.begin();
    //? Special handling of escape characters
    while (input_pointor != input_end) {
        //? simple characters
        if (*input_pointor != '\\') {
            *output_pointer++ = *input_pointor++;
        } else { //! escape characters
            unsigned char sequence_len = 2;
            if (input_pointor - input_end > 0) goto fail;
            switch (*(input_pointor + 1)) {
                case 'b': *output_pointer++ = '\b'; break;
                case 'f': *output_pointer++ = '\f'; break;
                case 'n': *output_pointer++ = '\n'; break;
                case 'r': *output_pointer++ = '\r'; break;
                case 't': *output_pointer++ = '\t'; break;
                case '\"': case '\\': case '/':
                    *output_pointer++ = *input_pointor; break;
                case 'u':
                    sequence_len = utf16_literal_to_utf8();
                    if (!sequence_len) goto fail;
                    break;
                default:
                    erron << "unexpect characters";
                    goto fail;
            }
            input_pointor += sequence_len;
        }
    }

    *output_pointer = '\0';
    
    item->type = SIMPLE_JSON_STRING;
    item->value = (char*)output;
    info << "value = " << output;
    input_buffer->offset = input_end - input_string.begin();
    input_buffer->offset++;
    return true;
fail:
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

std::ostream& operator<< (std::ostream& _cout, const simple_json& json) {
    json.print_value(_cout);
    return _cout;
}

void simple_json::print_value(std::ostream& os) const {
    os << "json: {\n\r\t";
    if (type == SIMPLE_JSON_NULL) {
        os << "type: json_null\n\r\t"
            << "content: null\n\r";
    } else if (type == SIMPLE_JSON_FALSE) {
        os << "type: json_bool\n\r\t"
            << "content: false\n\r";
    } else if (type == SIMPLE_JSON_TRUE) {
        os << "type: json_bool\n\r\t"
            << "content: true\n\r";
    } else if (type == SIMPLE_JSON_STRING) {
        os << "type: json_string\n\r\t"
            << "content: " 
            << std::get<std::string>(value) << "\n\r";
    }
    os << "}";
}