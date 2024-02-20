#ifndef STDEXEC___TYPE_TRAITS_HPP
#define STDEXEC___TYPE_TRAITS_HPP

#include "__config.hpp"

namespace stdexec {
  // A very simple std::declval replacement that doesn't handle void
  template <typename _Tp>
  _Tp&& __declval() noexcept;

  // __decay_t: An efficient implementation for std::decay
#if STDEXEC_HAS_BUILTIN(__decay)

#endif
}

#endif //STDEXEC___TYPE_TRAITS_HPP
