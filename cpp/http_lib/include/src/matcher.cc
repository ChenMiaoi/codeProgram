#include "../matcher.hpp"
#include <cstddef>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace httplib {
    namespace detail {
        PathParamsMatcher::PathParamsMatcher(const std::string& pattern) {
            std::size_t last_param_end = 0;
        #ifndef CPPHTTPLIB_NO_EXCEPTIONS
            std::unordered_set<std::string> param_name_set;
        #endif
            while (true) {
                const auto marker_pos = pattern.find(_marker, last_param_end);
                if (marker_pos == std::string::npos) break;

                // 获取到 /path/fragment/:capture中的/path/fragment
                _static_fragments.push_back(pattern.substr(last_param_end, marker_pos - last_param_end));

                const auto param_name_start = marker_pos + 1;
                auto sep_pos = pattern.find(_separator, param_name_start);
                if (sep_pos == std::string::npos) 
                    sep_pos = pattern.length();
                
                // 获取到 /path/fragment/:capture中的capture
                auto param_name = pattern.substr(param_name_start, sep_pos - param_name_start);
            #ifndef CPPHTTPLIB_NO_EXCEPTIONS
                if (param_name_set.find(param_name) != param_name_set.cend()) {
                    std::string msg = "Encounterd path parameter '" + param_name + 
                        "' multiple times in route pattern '" + pattern  + "'.";
                    throw std::invalid_argument(msg);
                }
            #endif
                _param_names.emplace_back(std::move(param_name));
                last_param_end = sep_pos + 1;
            }
            if (last_param_end < pattern.length())
                _static_fragments.push_back(pattern.substr(last_param_end));

            for (int i = 0; i < _static_fragments.size(); i++) {
                std::cout << "[Debug]: " << "\n\tfragments: " << _static_fragments[i] 
                                        << "\n\tname: " << _param_names[i] << std::endl;
            }
        }
        auto PathParamsMatcher::match(Request &request) const -> bool {
            request.set_matches();
            request.clear_path_params(_param_names.size());

            std::size_t start_pos = 0;
            for (size_t i = 0; i < _static_fragments.size(); i++) {
                const auto& fragment = _static_fragments.at(i);
                if (start_pos + fragment.size() > request.get_path_length())
                    return false;
                if (std::strncmp(request.get_path().c_str() + start_pos, fragment.c_str(), fragment.size()) != 0)
                    return false;

                start_pos += fragment.size();

                if (i >= _param_names.size()) continue;

                auto sep_pos = request.get_path().find(_separator, start_pos);
                if (sep_pos == std::string::npos) 
                    sep_pos = request.get_path_length();
                
                const auto& param_name = _param_names.at(i);

                request.get_params()
                       .emplace(param_name, request.get_path().substr(start_pos, sep_pos - start_pos));
                start_pos = sep_pos + 1;
            }
            return start_pos >= request.get_path_length();
        }
        auto RegexMatcher::match(Request &request) const -> bool {
            request.clear_path_params();
            std::smatch matches;
            auto ret = std::regex_match(request.get_path(), matches, _regex);
            // auto ret = std::regex_search(request.get_path(), _regex);
            request.set_matches(matches);
            return ret;
        }
    }
}