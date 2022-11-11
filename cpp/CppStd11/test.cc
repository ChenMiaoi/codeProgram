#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <map>
#include <memory>

namespace my {
    class A {
        friend std::ostream& operator<< (std::ostream& _cout, const A& a);
    public:
        A(int a = 0): _a(a) {}
        A(const A& a): _a(a._a) {
            std::cout << "A(const A& a): _a(a._a) -- 拷贝构造" << std::endl;
        }
        A(A&& a): _a(a._a) {
            std::cout << "A(A&& a): _a(a._a) -- 移动构造" << std::endl;
        }

        A& operator= (const A& a) {
            std::cout << "A& operator= (const A& a) -- 赋值重载" << std::endl;
            this->_a = a._a;
            return *this;
        }
    public:

    private:
        int _a;
    };

    std::ostream& operator<< (std::ostream& _cout, const A& a) {
        _cout << a._a;
        return _cout;
    }

    A to_string(A value) {
        A a(value);
        return a;
    }

    class StrVec {
    public:
        StrVec(int a = 0, int s = 0): _a(a), _s(s) {}
        StrVec(StrVec&& s) noexcept : _a(s._a), _s(s._s) {
            // noexcept 指定其是否能够抛出异常
            std::cout << "StrVec(StrVec&& s) noexcept : _a(s._a), _s(s._s)" << std::endl;
            // 假如是指针，如果在此处没有做深拷贝处理或者置空，析构函数时会将其移动的内存释放
        }

        StrVec& operator= (StrVec&& rhs) noexcept {
            if (this != &rhs) {
                _a = rhs._a;
                _s = rhs._s;
                std:: cout << "StrVec& operator= (StrVec&& rhs) noexcept" << std::endl;
            }
            return *this;
        }
        // StrVec& operator= (StrVec&& rhs) noexcept = delete;

        StrVec& operator= (std::initializer_list<std::string> il) {
            return *this;
        }

        int operator[] (size_t n) {
            return _a;
        }

        const int operator[] (size_t n) const {
            return _a;
        }

        bool operator() (int val) const {
            return val > 0;
        }
    private:
        int _a;
        int _s;
    };

    StrVec ref(int a) {
        StrVec b(a, 10);
        return b;
    }

    class Foo {
    public:
        Foo(int a = 0): _a(a) {}
        Foo& operator= (const Foo& foo) & { // 只可向可修改的左值赋值
            _a = foo._a;
            return *this;
        }

        Foo& operator+ (const Foo& foo) {
            _a += foo._a;
            return *this;
        }

        Foo operator+ (Foo&& foo) {
            _a += foo._a;
            return *this;
        }
    private:
        int _a;
    };

    class PrintString {
    public:
        PrintString(std::ostream& _os = std::cout, char c = ' ')
            : _cout(_os)
            , sep(c) {

        }

        void operator() (const std::string& s) const {
            _cout << s << sep;
        }
    private:
        char sep;
        std::ostream& _cout;
    };
}

void test1() {
    my::PrintString printString(std::cerr, '\n');
    printString("s");

    std::vector<std::string> vs {
            "hello", "world", "hey", "good"
    };
    std::for_each(vs.begin(), vs.end(), my::PrintString(std::cerr, '\t'));
    std::stable_sort(vs.begin(), vs.end(),
                     [](const std::string& str1, const std::string& str2) {
                         return str1.size() < str2.size();
                     });
    std::for_each(vs.begin(), vs.end(), my::PrintString(std::cerr, '\t'));

    std::plus<int> intAdd;
    int sum = intAdd(10, 20);
}

int add(int i, int j) {
    return i + j;
}

auto mod = [](int i, int j) {
    return i % j;
};

struct divide {
    int operator() (int i, int j) {
        return i / j;
    }
};



void test2() {
    std::map< std::string, std::function<int(int, int)> > binops {
            {"+", add},
            {"-", std::minus<int>()},
            {"/", divide()},
            {"*", [](int i, int j) { return i * j; }},
            {"%", mod}
    };
    std::string mode = "+";
    std::cout << binops[mode](10, 5);
    std::cout << binops["-"](10, 5);
    std::cout << binops["/"](10, 5);
    std::cout << binops["*"](10, 5);
    std::cout << binops["%"](10, 5);
}

int main() {
    test1();
    test2();
    return 0;
}