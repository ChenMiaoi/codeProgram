#ifndef __SIMPLE_JSON_HOOKS_H__
#define __SIMPLE_JSON_HOOKS_H__

#include "defs.h"
#include <functional>

typedef class internal_hooks {
    using AllocateFn    = std::function<SIMPLE_JSON_CDECL void*(size_t)>;
    using DeallocateFn  = std::function<SIMPLE_JSON_CDECL void(void*)>;
    using ReallocateFn  = std::function<SIMPLE_JSON_CDECL void*(void*, size_t)>;

public:
    internal_hooks();
public:
    AllocateFn   _allocate;
    DeallocateFn _deallocate;
    ReallocateFn _reallocate;
} internal_hooks;

#endif //! __SIMPLE_JSON_HOOKS_H__