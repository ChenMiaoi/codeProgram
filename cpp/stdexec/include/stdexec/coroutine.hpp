#ifndef STDEXEC_COROUTINE_HPP
#define STDEXEC_COROUTINE_HPP

#include "concepts.hpp"

#include "__detail/__config.hpp"
#include "__detail/__concepts.hpp"

#include <version>
#if __cpp_impl_coroutine >= 201902 && __cpp_lib_coroutine >= 201902
#include <coroutine>
namespace __coro = std;
#endif

namespace stdexec {
#if !STDEXEC_STD_NO_COROUTINES_
  // Define some concepts and utilities for working with awaitable
  template <typename _Tp>
  concept __await_suspend_result =
    __one_of<_Tp, void, bool> || __is_instance_of<_Tp, __coro::coroutine_handle>;
#endif
}

#endif //STDEXEC_COROUTINE_HPP
