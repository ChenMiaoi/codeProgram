#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <list>
#include <functional>
#include <algorithm>
#include <map>
#include <memory>

using std::cout;
using std::endl;

namespace Test1 {
//    template <typename _Ty>
//    int compare (const _Ty& v1, const _Ty& v2) {
//        if (v1 < v2) { return -1; }
//        if (v2 < v1) { return 1; }
//        return 0;
//    }

    // 模板非类型可以是一个整形或者一个指向对象或函数类型的指针或左值引用
    // 绑定到非类型整数参数的实参必须是一个常量表达式
    template <unsigned N, unsigned M>
    int compare (const char (&array1)[N], const char (&array2)[M]) {
        return strcmp(array1, array2);
    }

    // 用于各种类型正确的compare版本
    template <typename _Ty>
    int compare (const _Ty& v1, const _Ty& v2) {
        if (std::less<_Ty>() (v1, v2)) return -1;
        if (std::less<_Ty>() (v2, v1)) return 1;
        return 0;
    }

    void test() {
        compare<int>(1, 2);
        compare("hh", "hell");
    }
}

namespace Test2 {
    template <typename _Ty, typename _Tp, typename _Tv>
    class Base {

    };
    template <typename _Ty>
    class Blob: public Base<_Ty, _Ty, bool >{
    public:
        typedef _Ty __value_type;
        typedef std::string __string_type;
        typedef typename std::vector<_Ty>::size_type __size_type;
    public:
        inline Blob(): _data(std::make_shared<std::vector<_Ty>>()) {};
        inline Blob(std::initializer_list<_Ty> __il);
        _Ty& operator[] (__size_type __index);
        inline ~Blob() = default;
    public:
        _Ty& back();
        void pop_back();
        __size_type
        size() const { return _data->size(); }
        bool
        empty() const { return _data->empty(); }
    protected:
        void
        check(__size_type __index, const __string_type& __msg) const;
    private:
        std::shared_ptr<std::vector<_Ty>> _data;
    };

    template <typename _Ty>
    void Blob<_Ty>::check(Blob::__size_type index, const Blob::__string_type &msg) const {
        if (index >= _data->size()) throw std::out_of_range(msg);
    }

    template <typename _Ty>
    _Ty& Blob<_Ty>::back() {
        check(0, "back on empty Blob");
    }

    template <typename _Ty>
    _Ty& Blob<_Ty>::operator[](Blob::__size_type index) {
        check(index, "subscript out of range");
        return (*_data)[index];
    }

    template <typename _Ty>
    void Blob<_Ty>::pop_back() {
        check(0, "pop_back on empty Blob");
        _data->pop_back();
    }

    void test() {

    }
}

namespace Test3 {
    // !TIP 如果希望提前知道T的类型，那么需要使用typename去告知编译器
    //      注意，只允许使用typename关键字去告知
    //      注意，value_type只是STL::traits，其内部是typename _Ty value_type封装
    template <typename T>
    typename T::value_type top(const T& c) {
        if (!c.empty())
            return c.back();
        else
            return typename T::value_type();
    }

    template <typename T, typename fn = std::less<T>>
    int compare(const T& v1, const T& v2, fn f = fn()) {
        if (f(v1, v2)) return -1;
        if (f(v2, v1)) return 1;
        return 0;
    }

    void test() {
        std::queue<int, std::list<int>> s;
        cout << top(s);
        cout << std::queue<int>::value_type();
        cout << compare(1, 2, [](int a, int b) -> bool {
            return a < b;
        });
    }
}

namespace Test4 {
    class DebugDelete {
    public:
        DebugDelete(std::ostream& s = std::cerr): os(s) {}
        template<class T>
        void operator() (T* p) {
            os << "deleting unique_ptr" << std::endl;
            delete p;
        }

    private:
        std::ostream& os;
    };
    void test() {
        double* p = new double ;
        DebugDelete d;
        d(p); // 相当于调用了 DebugDelete::operator() (double* p)
        int* ip = new int ;
        DebugDelete() (ip);

        // use unique_ptr
        std::unique_ptr<int, DebugDelete> pk (new int, DebugDelete());
        std::unique_ptr<double, DebugDelete> sp (new double, DebugDelete());
        std::unique_ptr<std::string, DebugDelete> ssp (new std::string, DebugDelete());
    }
}

int main() {
//    Test1::test();
//    Test2::test();
//    Test3::test();
    Test4::test();
}