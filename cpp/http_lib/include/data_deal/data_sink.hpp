#ifndef __DATA_SINK_H__
#define __DATA_SINK_H__

#include "../def.hpp"

namespace httplib {
    class DataSink {
    public:
        DataSink(): _os(&_sb), _sb(*this) {}
    public:
        std::function<bool(const char* data, size_t data_len)> write;
        std::function<void(void)> done;
        std::function<void(const Headers& trailer)> do_with_trailer;
        std::ostream _os;
    private:
        class data_sink_streambuf: public std::streambuf {
        public:
            explicit data_sink_streambuf(DataSink& sink): _sink(sink) {}
        protected:
            std::streamsize xsputn(const char_type *s, std::streamsize n) override {
                _sink.write(s, static_cast<size_t>(n));
                return n;
            }
        private:
            DataSink& _sink;
        };

        data_sink_streambuf _sb;
    };

    using ContentProvider = 
        std::function<bool(size_t offset, size_t length, DataSink& sink)>;
    using ContentProviderWithoutLength = 
        std::function<bool(size_t offset, DataSink& sink)>;
}

#endif //!__DATA_SINK_H__