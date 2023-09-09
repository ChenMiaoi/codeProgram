#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "def.hpp"
#include "util.hpp"
#include "data_deal/content.hpp"
#include "data_deal/form_data.hpp"
#include "data_deal/data_sink.hpp"


#include <cstddef>
#include <string>

namespace httplib {
    const int INVAILD_PORT = -1;

    struct Request {
        /* request header */
        std::string _method;
        std::string _path;
        Headers     _headers;
        std::string _body;

        /* for config */
        int _remote_port = INVAILD_PORT;
        int _local_port  = INVAILD_PORT;
        std::string _remote_addr;
        std::string _local_addr;

        /* for server */
        std::string _version;
        std::string _target;
        Params _params;
        Ranges _ranges;
        Match  _matches;
        MultipartFormDataMap _files;
        std::unordered_map<std::string, std::string> _path_paramsl;

        /* for client */
        Progress _progress;
        ResponseHeadler _response_handler;
        ContentRecevierWithPorgress _content_receiver;
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            const SSL* ssl = nullptr;
        #endif

        /* 判断是否存在该头部 */
        auto has_header(const std::string& key) const -> decltype(auto); 
        /* 获取头部的值 */
        auto get_header_value(const std::string& key, size_t id = 0) const -> decltype(auto);

    private:
        size_t _redirect_count = CPPHTTPLIB_REDIRECT_MAX_COUNT;
        size_t _content_length = 0;
        ContentProvider _content_provider;
        bool _is_chunked_content_provider;
        size_t _authorization_count = 0;
    };

    inline auto Request::has_header(const std::string &key) const -> decltype(auto) {
        return detail::has_header(_headers, key);
    }
    inline auto Request::get_header_value(const std::string &key, size_t id) const -> decltype(auto) {
        return detail::get_header_value(_headers, key, id, "");
    }
}

#endif //!__REQUEST_H__