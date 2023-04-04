#ifndef __SHARE_WRAP_HPP__
#define __SHARE_WRAP_HPP__

#include <iostream>

template <typename __Ty>
class share_wrap {
private:
    __Ty* _ptr;
public:
    explicit share_wrap(__Ty* ptr = nullptr): _ptr(ptr) {}
    share_wrap(share_wrap<__Ty>& rhs) {
        share_wrap(std::move(rhs));
    }
    share_wrap(share_wrap<__Ty>&& rhs) {
        std::swap(_ptr, rhs._ptr);
    }
    ~share_wrap() { delete _ptr; }

    share_wrap<__Ty>& operator= (share_wrap<__Ty> rhs) {
        std::swap(_ptr, rhs._ptr);
        return *this;
    }
    share_wrap<__Ty>& operator= (share_wrap<__Ty>&& rhs) {
        std::swap(_ptr, rhs._ptr);
        return *this;
    }
    __Ty* operator*() const { return *_ptr; }
    __Ty& operator&() const { return _ptr; }
    operator bool() const { return _ptr; }
protected:

public:
    __Ty* get() const { return _ptr; }
};

#endif //! __SHARE_WRAP_HPP__