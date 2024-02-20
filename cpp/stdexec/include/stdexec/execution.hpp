#ifndef STDEXEC_EXECUTION_HPP
#define STDEXEC_EXECUTION_HPP

#include "__detail/__config.hpp"
#include "__detail/__execution_fwd.hpp"
#include "concepts.hpp"

#include <concepts>

STDEXEC_PRAGMA_PUSH()


namespace stdexec {
  // [execution.senders]
  struct sender_t {
    using sender_concept = sender_t;
  };

  namespace __detail {
    template <typename _Sender>
    concept __enable_sender =
      derived_from<typename _Sender::sender_concept, sender_t>
      || requires { typename _Sender::is_sender; }
      || __awaitable<_Sender, __env::__promise<empty_env>>;
  } //! namespace __detail

  template <typename _Sender>
  inline constexpr bool enable_sender = __detail::__enable_sender<_Sender>;
} //! namespace stdexec

STDEXEC_PRAGMA_POP()

#endif //STDEXEC_EXECUTION_HPP
