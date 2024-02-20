#ifndef STDEXEC_CONCEPTS_HPP
#define STDEXEC_CONCEPTS_HPP

#include "__detail/__concepts.hpp"

#include <version>

#if __has_include(<concepts>) && __cpp_lib_concepts >= 202002
#define STDEXEC_HAS_STD_CONCEPTS_HEADER() 1
#endif

#if STDEXEC_HAS_STD_CONCEPTS_HEADER()
#include <concepts>
#endif

namespace stdexec::__std_concepts {
  template <typename _Ap, typename _Bp>
  concept same_as = __same_as<_Ap, _Bp> && __same_as<_Bp, _Ap>;

#if STDEXEC_HAS_STD_CONCEPTS_HEADER()
  using std::integral;
  using std::derived_from;
  using std::convertible_to;
  using std::equality_comparable;
#endif
} //! namespace stdexec::__std_concepts

namespace stdexec {
  using namespace __std_concepts;
}

#endif //STDEXEC_CONCEPTS_HPP
