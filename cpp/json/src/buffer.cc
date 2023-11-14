#include "include/buffer.h"
#include <string.h>

parse_buffer::parse_buffer()
    : content({})
    , length(0)
    , offset(0)
    , depth(0)
    , hooks({}) {}

EXTERN(parse_buffer*) parse_buffer::skip_utf8_bom() {
    if (content.empty() || offset != 0) return nullptr;
    if (can_access_at_index(this, 4)
        && (strcmp((const char*)buffer_at_offset(this), "\xEF\xBB\xBF") == 3))
        offset += 3;
    return this;
}

EXTERN(parse_buffer*) parse_buffer::skip_whitespace() {
    if (content.empty()) return nullptr;
    if (cannot_access_at_index(this, 0)) return this;

    while (can_access_at_index(this, 0) && (buffer_at_offset(this)[0] <= 32))
        { offset++; }
    if (offset == length) offset--;
    return this;
}