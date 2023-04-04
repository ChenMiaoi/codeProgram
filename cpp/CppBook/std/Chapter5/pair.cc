#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <functional>

void f(std::pair<int, const char*>) {
    std::cout << "void f(std::pair<int, const char*>)" << std::endl;
}
void g(std::pair<const int, std::string>) {
    std::cout << "void g(std::pair<const int, std::string>)" << std::endl;
}

void foo() {
    /**
     * ! pair的Copy construction同时存在两个版本，一个接受相同参数的构造，第二个是模板构造，且能够接受隐式类型转换时使用
     * ! 并且，两个copy construction不会互相隐藏
    */
    std::pair<int, const char*> p(42, "hello");
    f(p);
    g(p);
}

/**
 * ! 自C++11起，如果pair<>用到某个类型中只有一个nonconstant copy，则会编译错误
*/

class A {
public:
    A() = default;
    // A (A&);
    A (const A&) {}
};

void func() {
    std::pair<A, int> p; // ! pair(const ...)
}

/**
 * ! pair给出最主要的三个构造函数为
 * ? copy construction
 * ? move construction
 * ? pair(piecewise_construct_t, tuple1, tuple2)，也就是说，第三个构造函数必须使用tuple，并且第一个参数必须是std::piecewise_construct
*/

class Foo {
public:
    Foo(std::tuple<int, float>) {
        std::cout << "Foo(std::tuple<int, float>)" << std::endl;
    }
    template <typename... Args>
    Foo(Args... args) {
        std::cout << "Foo(Args... args)" << std::endl;   
    }
};

void func1() {
    std::tuple<int, float> t(1, 2.22);

    std::pair<int, Foo> p1(42, t);

    // ! 只有std::piecewise_construct作为第一实参，class Foo才会被迫被使用接受tuple的元素
    // ! 并且，两个实参必须是tuple，因此对于42需要使用make_tuple转化,或者std::tuple(42)
    std::pair<int, Foo> p2(std::piecewise_construct, std::make_tuple(42), t);
}

/**
 * ! 便携make_pair()
 * ! 该模板函数能够使你无须类型就能生成一个pair对象
 * ? 且该模板有copy construction and move construction
 *  ? -> pair<T1, T2> make_pair（const T1& x, const T2& y)
 *  ? -> pair<T1, T2> make_pair（T1&& x, T2&& y)
*/

/**
 * ! 如果可能的话，make_pair()使用移动语义，否则拷贝语义。且其会蛀蚀(decay)实参，致使make_pair("a", "xy")产生出一个
 * ! pair<const char*, const char*> 而非一个 pair<const char[2], const char[3]>
*/

// void f(std::pair<int, const char*>) {}
// void g(std::pair<const int, std::string>) {}

void foo1() {
    f(std::make_pair(42, "empty"));
    g(std::make_pair(42, "chair")); // ? 发生隐式类型转换
}

/**
 * ? 当然的，自C++11起，你也可以使用初始化列表
*/

void foo2() {
    f({42, "empty"});
    g({42, "chair"});
}

/**
 * ! 并且，你可以强制指明使用移动语义通过std::move()或者引用语义通过std::ref() or cref()
*/

void foo3() {
    // ? 使用移动语义
    std::string s, t;
    auto p = std::make_pair(std::move(s), std::move(t));

    // ? 使用引用语义
    int i = 0;
    auto p1 = std::make_pair(std::ref(i), std::ref(i));
    ++p1.first;
    ++p1.second;
    std::cout << "i: " << i << std::endl;
}

/**
 * ! 可以使用tuple中的tie接口获取pair中的value
*/

void foo4() {
    std::pair<char ,char> p = std::make_pair('x', 'y');
    char c = 0;
    std::tie(std::ignore, c) = p; // ? 将第一个值忽略掉，获取p中的第二个值
    std::cout << "p::second: " << c << std::endl;
}

/**
 * ! pair之间的比较重载了操作符，而且first elem的优先级高于second elem
*/

int main() {
    std::pair<std::string, int> p1("Hello", 1);
    std::pair<std::string, int> p2("Hello", 1);
    std::cout << p1.first << p2.second << std::endl;

    /**
     * ! 自C++11起，pair提供了一套tuple-like接口，可以使用tuple_size<>::value获取元素个数，使用tuple_element<>::type获取类型
     * ! 也可以用get()获取first或second
    */
    using IntFloatPair = std::pair<int, float>;
    IntFloatPair p(42, 3.14);
    std::cout << std::get<0>(p) << " " << std::get<1>(p) << std::endl;
    std::tuple_element<0, IntFloatPair>::type i = 2;
    std::cout << std::tuple_size<IntFloatPair>::value << std::endl;

    func();
    foo1();
    foo2();
    foo3();
    foo4();
    return 0;
}