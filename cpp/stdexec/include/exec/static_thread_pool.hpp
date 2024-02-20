#ifndef __EXEC_STATIC_THREAD_POOL_HPP
#define __EXEC_STATIC_THREAD_POOL_HPP

#include "../stdexec/__detail/__config.hpp"
#include "../stdexec/execution.hpp"

#include <cstdint>
#include <utility>

namespace exec {
  struct bwos_params {
    std::size_t num_blocks {32};
    std::size_t block_size {8};
  };

  namespace _pool_ {
    using namespace stdexec;

    /// Splits `n` into `size` chunks distributing `n % size` evenly between ranks.
    /// Returns `[begin, end)` range in `n` for a given `rank`.
    /// Example:
    /// @code
    /// //         n_items  thread  n_threads
    /// even_share(     11,      0,      3); // -> [0,  4) -> 4 items
    /// even_share(     11,      1,      3); // -> [4,  8) -> 4 items
    /// even_share(     11,      2,      3); // -> [8, 11) -> 3 items
    /// @endcode
    template <typename Shape>
    std::pair<Shape, Shape> even_share(Shape n, std::uint32_t rank, std::uint32_t size) noexcept {
      STDEXEC_ASSERT(n >= 0);
      using ushape_t = std::make_unsigned_t<Shape>;
      const auto avg_per_thread = static_cast<ushape_t>(n) / size;
      const auto n_big_share    = avg_per_thread + 1;
      const auto big_shares     = static_cast<ushape_t>(n) % size;
      const auto is_big_share   = rank < big_shares;
      const auto begin = is_big_share
                          ? n_big_share * rank
                          : n_big_share * big_shares + (rank - big_shares) * avg_per_thread;
      const auto end   = begin + (is_big_share ? n_big_share : avg_per_thread);

      return std::make_pair(static_cast<Shape>(begin), static_cast<Shape>(end));
    }


  } //! _pool_
} //! exec

#endif //! __EXEC_STATIC_THREAD_POOL_HPP
