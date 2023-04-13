#ifndef CHAPTER06_LINE_READER_H
#define CHAPTER06_LINE_READER_H

#include <cstddef>
#include <string>
#include <iostream>

class istream_line_reader {
public:
    class iterator {
    private:
        std::istream* _stream;
        std::string _line;
    public:
        typedef ptrdiff_t difference_t;
        typedef std::string value_type;
        typedef const value_type* pointer;
        typedef const value_type& reference;
        typedef std::input_iterator_tag iterator_category;
    public:
        iterator() noexcept: _stream(nullptr) {}
        explicit iterator(std::istream& is): _stream(&is) {
            ++*this;
        }

        reference operator* () const noexcept { return _line; }
        pointer   operator-> () const noexcept { return &_line; }
        iterator& operator++() {
            getline(*_stream, _line);
            if (!*_stream)
                _stream = nullptr;
            return *this;
        }
        iterator operator++ (int) {
            iterator temp(*this);
            ++*this;
            return temp;
        }
        bool operator== (const iterator& rhs) const noexcept {
            return _stream == rhs._stream;
        }
        bool operator!= (const iterator& rhs) const noexcept {
            return !operator==(rhs);
        }
    };
private:
    std::istream* _stream;
public:
    istream_line_reader() noexcept: _stream(nullptr) {}
    explicit istream_line_reader(std::istream& is) noexcept: _stream(&is) {}

    iterator begin() { return iterator(*_stream); }
    iterator end() const noexcept { return iterator(); }
};

#endif //CHAPTER06_LINE_READER_H
