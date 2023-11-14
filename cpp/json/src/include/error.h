#ifndef __SIMPLE_JSON_ERROR_H__
#define __SIMPLE_JSON_ERROR_H__

#include "defs.h"

typedef class error {
private:
    const unsigned char* _json;
    size_t _position;
public:
    error();
    error(const unsigned char* json, size_t position);

    EXTERN(const unsigned char*) get_json() const;
    EXTERN(size_t) get_position() const;
} error;

#endif //! __SIMPLE_JSON_ERROR_H__