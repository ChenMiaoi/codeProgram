#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include "def.hpp"
#include "data_deal/content.hpp"
#include "data_deal/data_sink.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace httplib {
    const int INVAILD_STATUS = -1;

    struct Response {
    public:
        Response() = default;
        Response(const Response&) = default;
        Response(Response&&) = default;
        Response& operator= (const Response&) = default;
        Response& operator= (Response&&) = default;
        ~Response() {
            if (_content_releaser) {
                _content_releaser(_content_provider_success);
            }
        }
    public:
        /* 检查是否存在头部 */
        auto has_header(const std::string& key) const -> bool;
        /* 获取头部的值，若存在多个，用id来索引 */
        auto get_header_value(const std::string& key, size_t id = 0) const -> std::string;
        auto get_header_value_u64(const std::string& key, size_t id = 0) const -> uint64_t;
        /* 获取有多少个相同头部数量 */
        auto get_header_value_count(const std::string& key) const -> size_t;

        /* 设置头部 */
        auto set_header(const std::string& key, const std::string& val) -> void;
        /* 设置重定向相应，并设置Location字段的值为url */
        auto set_redirect(const std::string& url, int status = 302) -> void;
        /* 更新 HTTP 响应的内容和头部字段，确保响应的内容和类型正确设置。 */
        auto set_content(const std::string& s, const std::string& content_type) -> void;
        auto set_content(const char* s, size_t n, const std::string& content_type) -> void;
        /* 根据提供的信息，动态生成相应内容 */
        auto set_content_provider(size_t length, const std::string& content_type, 
            ContentProvider provider, ContentProviderResourceReleaser resource_releaser = nullptr) -> void;
        auto set_content_provider(const std::string& content_type,
            ContentProviderWithoutLength provider, ContentProviderResourceReleaser resource_releaser = nullptr) -> void;
        /* 设置分块内容提供器，动态生成相应，并使用分块传输编码 */
        auto set_chunked_content_provider(const std::string& content_type,
            ContentProviderWithoutLength provider, ContentProviderResourceReleaser resource_releaser = nullptr) -> void;
    private:
        std::string _version;
        int _status = INVAILD_STATUS;
        std::string _reason;
        Headers _headers;
        std::string _body;
        std::string _location;

        size_t _content_length = 0;
        bool _is_chunked_content_provider = false;
        bool _content_provider_success = false;
        ContentProvider _content_provider;
        ContentProviderResourceReleaser _content_releaser;
    };
}

#endif //!__RESPONSE_H__