#include "../request.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <map>
#include <regex>
#include <string>
#include <unordered_map>

namespace httplib {
    auto Request::has_header(const std::string &key) const -> bool {
        return detail::has_header(_headers, key);
    }
    auto Request::get_header_value(const std::string &key, size_t id) const -> std::string {
        return std::string {detail::get_header_value(_headers, key, id, "")};
    }
    auto Request::get_header_value_u64(const std::string &key, size_t id) const -> uint64_t {
        return detail::get_header_value_u64(_headers, key, id, 0);
    }
    auto Request::get_header_value_count(const std::string &key) const -> size_t  {
        auto r = _headers.equal_range(key);
        return static_cast<size_t>(std::distance(r.first, r.second));
    }
    auto Request::set_header(const std::string &key, const std::string &val) -> void {
        if (!detail::has_crlf(key) && !detail::has_crlf(val)) {
            _headers.emplace(key, val);
        }
    }
    auto Request::has_param(const std::string &key) const -> bool {
        return _params.find(key) != _params.end();
    }
    auto Request::get_params() const -> std::unordered_map<std::string, std::string> {
        return _path_params;
    }
    auto Request::get_param_value(const std::string &key, size_t id) const -> std::string {
        auto rng = _params.equal_range(key);
        auto it  = rng.first;
        std::advance(it, static_cast<ssize_t>(id));

        if (it != rng.second) return it->second;
        return {};
    }
    auto Request::get_param_value_count(const std::string &key) const -> size_t {
        auto r = _params.equal_range(key);
        return static_cast<size_t>(std::distance(r.first, r.second));
    }
    auto Request::has_file(const std::string &key) const -> bool {
        return _files.find(key) != _files.end();
    }
    auto Request::get_file_value(const std::string &key) const -> MultipartFormData {
        auto it = _files.find(key);
        if (it != _files.end()) return it->second;
        return {};
    }
    auto Request::get_file_values(const std::string &key) const -> MultipartFormDataItems {
        MultipartFormDataItems values;
        auto rng = _files.equal_range(key);
        std::transform(rng.first, rng.second, std::back_inserter(values), [](const auto& var){
            return var.second;
        });
        return values;
    }
    auto Request::is_multi_form_data() const -> bool {
        const auto& content_type = get_header_value("Content-Type");
        return !content_type.rfind("multipart/form-data", 0);
    }
    auto Request::set_matches(const Match& matches) -> void {
        _matches = matches;
    }
    auto Request::clear_path_params(size_t reserve_len) -> void {
        _path_params.clear();
        _path_params.reserve(reserve_len);
    }
    auto Request::set_path(const std::string& path) -> void {
        _path = path;
    }
    auto Request::get_path() const -> const std::string& {
        return _path;
    }
    auto Request::get_path_length() const -> size_t {
        return _path.size();
    }
    auto Request::get_matches() const -> Match {
        return _matches;
    }
}