#ifndef __SHARE_WRAP_HPP__
#define __SHARE_WRAP_HPP__

#include <iostream>

struct share_count {
    share_count(): _count(1) {}
    void add_count() { ++_count; }
    long reduce_count() { return --_count; }
    long get_count() const { return _count; }
private:
    long _count;
};

template <typename __Ty>
class share_wrap {
    template<typename U>
    friend class share_wrap;
private:
    __Ty* _ptr;
    share_count* _shared_count;
public:
    explicit share_wrap(__Ty* ptr = nullptr): _ptr(ptr) {
        if (ptr) {
            _shared_count = new share_count();
        }
    }

    template<typename T>
    share_wrap(const share_wrap<T>& rhs, T* ptr) {
        _ptr = ptr;
        if (_ptr) {
            rhs._shared_count->add_count();
            _shared_count = rhs._shared_count;
        }
    }
    template<typename T>
    share_wrap(share_wrap<T>&& rhs) {
        std::swap(_ptr, rhs._ptr);
        if (_ptr) {
            std::swap(_shared_count, rhs._shared_count);
//            this->_shared_count = rhs._shared_count;
            rhs._ptr = nullptr;
        }
    }
    template<typename T>
    share_wrap<T>& operator= (share_wrap<T>&& rhs) {
        std::swap(_ptr, rhs._ptr);
        std::swap(_shared_count, rhs._shared_count);
        return *this;
    }
    share_wrap(const share_wrap& rhs) {
        std::swap(_ptr, rhs._ptr);
        if (_ptr) {
            rhs._shared_count->add_count();
            _shared_count = rhs._shared_count;
        }
    };

    template<typename T>
    share_wrap(const share_wrap<T>& rhs) {
        std::swap(_ptr, rhs._ptr);
        if (_ptr) {
            rhs._shared_count->add_count();
            _shared_count = rhs._shared_count;
        }
    };
    share_wrap& operator= (share_wrap& rhs) {
        _ptr = rhs._ptr;
        rhs._shared_count->add_count();
        _shared_count = rhs._shared_count;
//        std::swap(_ptr, rhs._ptr);
//        std::swap(_shared_count, rhs._shared_count);
        return *this;
    };
    ~share_wrap() {
        if (_ptr && !_shared_count->reduce_count()) {
            delete _ptr;
            delete _shared_count;
        }
    }

    //    share_wrap(share_wrap<__Ty>& rhs) {
    //        share_wrap(std::move(rhs));
    //    }
    //    share_wrap<__Ty>& operator= (share_wrap<__Ty> rhs) {
    //        std::swap(_ptr, rhs._ptr);
    //        return *this;
    //    }
    __Ty* operator*() const { return *_ptr; }
    __Ty& operator&() const { return _ptr; }
    operator bool() const { return _ptr; }
protected:

public:
    __Ty* get() const { return _ptr; }
    long use_count() const {
        if (_ptr) {
            return _shared_count->get_count();
        }
        return 0;
    }
};

template<typename T, typename U>
share_wrap<T> dynamic_pointer_cast(const share_wrap<U>& rhs) {
    T* ptr = dynamic_cast<T*>(rhs.get());
    return share_wrap<T>(rhs, ptr);
}

template<typename T, typename U>
share_wrap<T> static_pointer_cast(const share_wrap<U>& rhs) {
    T* ptr = static_cast<T*>(rhs.get());
    return share_wrap<T>(rhs, ptr);
}

template<typename T, typename U>
share_wrap<T> reinterpret_pointer_cast(const share_wrap<U>& rhs) {
    T* ptr = reinterpret_cast<T*>(rhs.get());
    return share_wrap<T>(rhs, ptr);
}

template<typename T, typename U>
share_wrap<T> const_pointer_cast(const share_wrap<U>& rhs) {
    T* ptr = const_cast<T*>(rhs.get());
    return share_wrap<T>(rhs, ptr);
}

#endif //! __SHARE_WRAP_HPP__