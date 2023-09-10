#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "def.hpp"
#include "util.hpp"
#include "data_deal/content.hpp"
#include "data_deal/form_data.hpp"
#include "data_deal/data_sink.hpp"


#include <cstddef>
#include <cstdint>
#include <string>

namespace httplib {
    const int INVAILD_PORT = -1;

    struct Request {
    private:
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

    public:
        /* 判断是否存在该头部 */
        auto has_header(const std::string& key) const -> bool; 
        /* 获取头部的值 */
        auto get_header_value(const std::string& key, size_t id = 0) const -> std::string;
        /* uint64_t 类型 */
        auto get_header_value_u64(const std::string &key, size_t id = 0) const -> uint64_t; 
        /* 获取头部的数量 */
        auto get_header_value_count(const std::string& key) const -> size_t;
        /* 设置头部 */
        auto set_header(const std::string& key, const std::string& val) -> void;

        auto has_param(const std::string& key) const -> bool;
        auto get_param_value(const std::string& key, size_t id = 0) const -> std::string;
        auto get_param_value_count(const std::string& key) const -> size_t; 

        auto has_file(const std::string &key) const -> bool;
        auto get_file_value(const std::string &key) const -> MultipartFormData;
        auto get_file_values(const std::string &key) const -> MultipartFormDataItems;

        auto is_multi_form_data() const -> bool;


    private:
        size_t _redirect_count = CPPHTTPLIB_REDIRECT_MAX_COUNT;
        size_t _content_length = 0;
        ContentProvider _content_provider;
        bool _is_chunked_content_provider;
        size_t _authorization_count = 0;
    };
}

#endif //!__REQUEST_H__