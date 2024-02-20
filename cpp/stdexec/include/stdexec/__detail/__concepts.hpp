#ifndef STDEXEC___CONCEPTS_HPP
#define STDEXEC___CONCEPTS_HPP

#include "__config.hpp"

namespace stdexec {
#if STDEXEC_GCC()
  template <typename _Ap, typename _Bp>
  concept __same_as = __is_same_as(_Ap, _Bp);
#else
  template <typename _Ap, typename _Bp>
  inline constexpr bool __same_as_v = false;

  template <typename _Ap>
  inline constexpr bool __same_as_v<_Ap, _Ap> = true;

  template <typename _Ap, typename _Bp>
  concept __same_as = __same_as_v<_Ap, _Bp>;
#endif
}

#endif //STDEXEC___CONCEPTS_HPP
