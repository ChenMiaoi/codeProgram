#ifndef __CONTENT_H__
#define __CONTENT_H__

#include "data_sink.hpp"
#include "form_data.hpp"
#include <functional>

namespace httplib {
    using ContentProviderResourceReleaser = std::function<void(bool success)>;

    using ContentRecevier = std::function<bool(const char* data, size_t data_length)>;
    using ContentRecevierWithPorgress = 
        std::function<bool(const char* data, size_t data_length, uint64_t offset, uint64_t total_length)>;
    using MultipartContentHeader = std::function<bool(const MultipartFormData& file)>;

    class ContentReader {
    public:
        using Reader = 
            std::function<bool(ContentRecevier receiver)>;
        using MultipartReader = 
            std::function<bool(MultipartContentHeader header, ContentRecevier receiver)>;

        ContentReader(Reader reader, MultipartReader multi_reader)
            : _reader(std::move(reader))
            , _multi_reader(std::move(multi_reader)) {}

        bool operator() (MultipartContentHeader header, ContentRecevier receiver) const {
            return _multi_reader(std::move(header), std::move(receiver));
        }

        bool operator() (ContentRecevier receiver) const {
            return _reader(std::move(receiver));
        }
        
        Reader _reader;
        MultipartReader _multi_reader;
    };
}

#endif //!__CONTENT_H__