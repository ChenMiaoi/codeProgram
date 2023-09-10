#include "../util.hpp"
#include "../response.hpp"
#include <cstddef>
#include <cstdint>
#include <iterator>

namespace httplib {

    auto Response::has_header(const std::string &key) const -> bool {
        return _headers.find(key) != _headers.end();
    }
    auto Response::get_header_value(const std::string &key, size_t id) const -> std::string {
        return detail::get_header_value(_headers, key, id, "");
    }
    auto Response::get_header_value_u64(const std::string &key, size_t id) const -> uint64_t {
        return detail::get_header_value_u64(_headers, key, id, 0);
    }
    auto Response::get_header_value_count(const std::string &key) const -> size_t {
        auto rng = _headers.equal_range(key);
        return static_cast<size_t>(std::distance(rng.first, rng.second));
    }
    auto Response::set_header(const std::string &key, const std::string &val) -> void {
        if (!detail::has_crlf(key) || !detail::has_crlf(val))
            _headers.emplace(key, val);
    }
    auto Response::set_redirect(const std::string &url, int status) -> void {
        if (!detail::has_crlf(url)) {
            set_header("Location", url);
            if (300 <= status && status < 400) 
                this->_status = status;
            else
                this->_status = 302;
        }
    }
    auto Response::set_content(const char* s, size_t n, const std::string& content_type) -> void {
        _body.assign(s, n);
        auto rng = _headers.equal_range("Content-Type");
        _headers.erase(rng.first, rng.second);
        set_header("Content-Type", content_type);
    }
    auto Response::set_content(const std::string& s, const std::string& content_type) -> void {
        set_content(s.data(), s.size(), content_type);
    }
    auto Response::set_content_provider(size_t length, const std::string& content_type, 
        ContentProvider provider, ContentProviderResourceReleaser resource_releaser) -> void {
        set_header("Content-Type", content_type);
        _content_length = length;
        if (_content_length > 0)
            _content_provider = std::move(provider);
        _content_releaser = resource_releaser;
        _is_chunked_content_provider = false;
    }
    auto Response::set_content_provider(const std::string& content_type,
        ContentProviderWithoutLength provider, ContentProviderResourceReleaser resource_releaser) -> void {
        set_header("Content-Type", content_type);
        _content_length = 0;
        _content_provider = detail::ContentProviderAdapter(std::move(provider));
        _content_releaser = resource_releaser;
        _is_chunked_content_provider = false;
    }
    auto Response::set_chunked_content_provider(const std::string &content_type, 
        ContentProviderWithoutLength provider, ContentProviderResourceReleaser resource_releaser) -> void {
        set_header("Content-Type", content_type);
        _content_length = 0;
        _content_provider = detail::ContentProviderAdapter(std::move(provider));
        _content_releaser = resource_releaser;
        _is_chunked_content_provider = false;
    }
}