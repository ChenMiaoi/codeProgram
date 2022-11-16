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

namespace Test3 {
    class SmallInt {
    public:
        SmallInt(int i = 0): var(i) {
            if (i < 0 || i > 255) {
                throw std::out_of_range("Bad SmallInt value");
            }
        }

        explicit operator int() const {
            // explicit将隐式类型转换必须通过显示来进行
            return var;
        }
    private:
        std::size_t var;
    };

    struct A {
        // 转换构造函数，和普通构造函数一致，但是只允许一个参数
        // 例如：A a; a = 20;
        // 假如刚好有多个转换构造函数，且普通函数重载的参数是不同的转换构造函数，那么会产生二义性问题
        A(int a) {

        }
    };

    struct B {
        B(int b) {

        }
    };

    struct C {
        C(double c) {

        }
    };
}

void manip(const Test3::A& a) {

}

void manip(const Test3::B& b) {

}

void manip(const Test3::C& c) {

}
void test3() {
    Test3::SmallInt smallInt;
    smallInt = static_cast<int>(smallInt) + 255;
    std::cout << static_cast<int>(smallInt) << std::endl;
    Test3::A a(10);
    a = 20;

    // manip(10); 转化构造函数产生的二义性问题
    manip(Test3::A(10));
    manip(Test3::B(20));
    // manip(10); 注意，哪怕转换构造函数的参数类型不一样，由于int也可以隐式转化double因此，也会造成二义性问题
}

namespace Test4 {
    class SmallInt {
        friend SmallInt operator+ (const SmallInt& smallInt1, const SmallInt& smallInt2);
    public:
        SmallInt(int a = 0): var(a) {} // 转换构造函数，默认从0转换
        operator int() const { // 类型转换运算符， SmallInt -> int
            std::cout << "operator int() const -- SmallInt -> int (" << __LINE__ << "rows)" << std::endl;
            return var;
        }

//        SmallInt operator+ (const SmallInt& smallInt) {
//
//        }
    private:
        std::size_t var;
    };

    SmallInt operator+ (const SmallInt& smallInt1, const SmallInt& smallInt2) {
        static int count = 0;
        std::cout << "SmallInt operator+ (const SmallInt& smallInt1, const SmallInt& smallInt2): " << count++ << std::endl;
        // 此处不能用过operator int() 来复用，如果使用这样，会导致operator+无限递归
        return smallInt1 + smallInt2;
    }

    void test() {
        SmallInt s1, s2;
        SmallInt s3 = s1 + s2;
        // s3 = s1 + s2 实际上是调用了 operator+ 然后得到的返回值进行转换构造
        // int i = s3 + 0; 此处的+号，是因为operator+ 和 转化构造函数发生了冲突
    }
}

#if 0
namespace Test5 {
    class Quote {
    public:
        Quote() = default;
        Quote(const std::string& book, double sales_price)
            : bookNo(book)
            , price(sales_price)
        {}

        virtual ~Quote() = default;
    public:
        std::string isbn() const {
            return "hello";
        }

        virtual double net_price(std::size_t n) const;
    protected:
        double price = 0.0;
    private:
        std::string bookNo;
    };

    class Bulk_quote: public Quote {
    public:
        Bulk_quote() {
            Quote("hellp", 20.0);
        }
    public:
        double net_price(std::size_t n) const override {
            // override 关键字告诉编译器该函数重载于父类的某个虚函数
            std::cout << "double Bulk_quote::net_price(std::size_t n) const override" << std::endl;
            return n;
        }
    };

    double print_total(std::ostream& _os, const Quote& item, size_t n) {
        double ret = item.net_price(n);
        // _os << item.isbn();
        return ret;
    }

    void test() {
        Quote basic;
        Bulk_quote bulk;
        // print_total(std::cout, basic, 5);
        print_total(std::cout, Bulk_quote(), 5);
    }
}
#endif

#if 0
namespace Test6 {
    class Animal {
    public:
        Animal() = default;
        Animal(int i = 0): _a(i) {}
    public:
        virtual void sleep() const;
    private:
        int _a;
    };

    class Cat: public Animal {
    public:
        Cat(int i = 0): Animal(1), _b(i) {}
    public:
        void sleep() const override {
            std::cout << "void Cat::sleep() override" << std::endl;
        }
    private:
        int _b;
    };

    class Dog: public Animal {
    public:
        Dog(int i = 0): Animal(1), _c(i) {}
    public:
        void sleep() const override {
            std::cout << "void Dog::sleep() override" << std::endl;
        }
    private:
        int _c;
    };

    void Sleep(const Animal& animal) {
        animal.sleep();
    }

    void test6() {
        Cat cat;
        Dog dog;
        Sleep(cat);
        Sleep(dog);

        // Animal animal1;
        // Animal& animal = cat;
        // Cat& cat1 = animal1; 可以从衍生类对基类的隐式转化，可以从大切片到小，不能从小增加到大
    }
}
#endif

namespace Test7 {
    class Base {

    };

    class Last final: Base {

    };

    void test7() {

    }
}

namespace Test8 {
    class Base {
    public:
        virtual double net_price(double price) const = 0;
    };

    double Base::net_price(double price) const {
        std::cout << "double Base::net_price(double price) const" << std::endl;
        return 0;
    }

    class Derive: public Base {
    public:
        double net_price(double price) const {
            std::cout << "double Derive::net_price(double price) const" << std::endl;
            return 0;
        }
    };

    void func(const Base& base) {
        base.net_price(0);
    }

    void test8() {
        Derive derive;
        func(derive);
    }
}

int main() {
    // test1();
    // test2();
    // test3();
    // Test4::test();
    // Test5::test();
    // Test6::test6();
    // Test7::test7();
    Test8::test8();
    return 0;
}