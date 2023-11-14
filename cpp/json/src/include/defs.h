#ifndef __SIMPLE_JSON_DEFS_H__
#define __SIMPLE_JSON_DEFS_H__

// #define __WINDOWS__

#if defined(__WINDOWS__) && (defined(_MSC_VER) || defined (_WIN64))
#   define SIMPLE_JSON_CDECL    __cdecl
#   define SIMPLE_JSON_STDCALL  __stdcall
#else
#   define SIMPLE_JSON_CDECL
#   define SIMPLE_JSON_STDCALL
#endif

#define EXTERN(type) __attribute__((visibility("default"))) type

#define SIMPLE_JSON_VERSION_MAJOR   0
#define SIMPLE_JSON_VERSION_MINOR   1
#define SIMPLE_JSON_VERSION_PATCH   0

#ifndef SIMPLE_JSON_NESTING_LIMIT
#   define SIMPLE_JSON_NESTING_LIMIT    1000
#endif //! SIMPLE_JSON_NESTING_LIMIT

#include "log.h"

#endif //! __SIMPLE_JSON_DEFS_H__