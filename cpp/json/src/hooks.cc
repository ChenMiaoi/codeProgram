#include "include/hooks.h"

#if defined(__WINDOWS__) && (defined(_MSC_VER) || defined (_WIN64))
static void* SIMPLE_JSON_CDECL internal_malloc(size_t size) {
    return malloc(size);
}
static void SIMPLE_JSON_CDECL internal_free(void* ptr) {
    return free(ptr);
}
static void* SIMPLE_JSON_CDECL internal_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}
#else //! not windows
#   define internal_malloc  malloc
#   define internal_free    free
#   define internal_realloc realloc
#endif

internal_hooks::internal_hooks() 
    : _allocate(internal_malloc)
    , _deallocate(internal_free)
    , _reallocate(internal_realloc)
{}