#ifndef __FORM_DATA_H__
#define __FORM_DATA_H__

#include "../def.hpp"
#include "data_sink.hpp"

namespace httplib {
     struct MultipartFormData {
        std::string name;
        std::string content;
        std::string filename;
        std::string content_type;
    };

    struct MultipartFormDataProvider {
        std::string name;
        ContentProviderWithoutLength provider;
        std::string filename;
        std::string content_type;
    };

    using MultipartFormDataItems = std::vector<MultipartFormData>;
    using MultipartFormDataMap   = std::multimap<std::string, MultipartFormData>;
    using MultipartFormDataProviderItems = std::vector<MultipartFormDataProvider>;
}

#endif //!__FORM_DATA_H__