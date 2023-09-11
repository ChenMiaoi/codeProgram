#ifndef __MATCHER_H__
#define __MATCHER_H__

#include "def.hpp"
#include "request.hpp"
#include <regex>
#include <vector>
#include <cstring>

namespace httplib {
    namespace detail {
        class MatcherBase {
        public:
            virtual ~MatcherBase() = default;

            // 匹配Request path
            virtual auto match(Request& request) const -> bool = 0;
        };

        /**
        * 捕获参数，存储在Request::_path_params中
        * 主要格式为：/path/fragments/:capture/more/../:seconde_capture
        * 也就是说，以/开始，然后直到：结束，为一个param，直到匹配到最后一个/
        */
        class PathParamsMatcher: public MatcherBase {
        public:
            PathParamsMatcher(const std::string& pattern);

            auto match(Request& request) const -> bool override;
        private:
            static constexpr char _marker    = ':';
            static constexpr char _separator = '/';
            std::vector<std::string> _static_fragments;
            std::vector<std::string> _param_names;
        };

        /**
        * 通过正则表达式来捕获参数
        */
        class RegexMatcher: public MatcherBase {
        public:
            RegexMatcher(const std::string& pattern): _regex(pattern) {}

            auto match(Request& request) const -> bool override;
        private:
            std::regex _regex;
        };
    } // namespace detail
} // namespace httplib

#endif //!__MATCHER_H__
