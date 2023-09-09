#ifndef __DETAIL_H__
#define __DETAIL_H__

// #include "def.hpp"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iterator>
#include <string>
#include <type_traits>
#include <memory>
#include <utility>
#include <functional>

namespace httplib {
    namespace detail {
        // lower c++14
        #if __cplusplus < 201402L
            template <class T, class ... Args>
            typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
            make_unique(Args&&... args) {
                return std::unique_ptr<T>(new T(std::forward<T>(args)...));
            }

            template <class T, class ... Args>
            typename std::enable_if<std::is_array<T>::value, std::unique_ptr<T>>::type
            make_unique(std::size_t n) {
                return std::unique_ptr<T>(new typename std::remove_extent<T>::type[n]);
            }
        #endif
        struct ci {
            bool operator() (const std::string& s1, const std::string& s2) const {
                return std::lexicographical_compare(
                    std::begin(s1), std::end(s1),
                    std::begin(s2), std::end(s2),
                    [](unsigned char c1, unsigned char c2) {
                        return ::tolower(c1) < ::tolower(c2);
                    });
            }
        };

        /*
        * 对RAII技术的实现
        * @ref "http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4189".
        */
        struct scope_exit {
            explicit scope_exit(std::function<void(void)>&& f)
                : exit_function(std::move(f)), execute_on_destruction(true) {}

            scope_exit(scope_exit&& rhs)
                : exit_function(std::move(rhs.exit_function))
                , execute_on_destruction(rhs.execute_on_destruction) {
                    rhs.release();
            }

            ~scope_exit() {
                if (execute_on_destruction) { this->exit_function(); }
            }

            void release() { this->execute_on_destruction = false; }
        private:
            scope_exit(const scope_exit&) = delete;
            scope_exit& operator=(scope_exit&&) = delete;
            void operator= (const scope_exit&) = delete;
        private:
            std::function<void(void)> exit_function;
            bool execute_on_destruction;
        };
    } // namespace detail
} // namespace httplib

#endif //!__DETAIL_H__