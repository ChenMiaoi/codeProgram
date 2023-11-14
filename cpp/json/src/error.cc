#include "include/error.h"

error::error(): _json(nullptr), _position(0) {}
error::error(const unsigned char* json, size_t position)
    : _json(json), _position(position) {}

EXTERN(const unsigned char*) error::get_json() const
    { return _json; }
EXTERN(size_t) error::get_position() const
    { return _position; }