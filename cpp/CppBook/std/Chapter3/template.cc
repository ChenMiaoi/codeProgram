#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include <bitset>

/**
 * 从C++11起，template可接受不定参数
*/

void print() {}

/**
 * ? 对于以下例子是否有效还有待研究
 * 而sizeof...(args)会生成实参个数
*/

template <typename T>
void print(const T& arg) {
    std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
    std::cout << sizeof...(args) << " : " <<  firstArg << std::endl;
    print(args...);
}

/**
 * ! lambda的类型是一个不具名的function object(或称为functor)，每一个lambda表达式的类型都是独一无二的
 * ! 如果想要根据其类型声明对象，通常借助与template或auto，但是这样还是不太方便，可以通过std::function<> class template
 * ! 指明一个一般化类型给functional programming使用
*/

std::function<int(int, int)> returnLambda() {
    return [] (int x, int y) { 
        return x * y;
    };
}

/**
 * ? 新关键字 decltype可让编译器找出表达式类型，其实就是typeof的一种扩展
*/

std::map<std::string, float> coll;
decltype(coll)::value_type elem;

/**
 * ? 新的函数声明语法
*/

template <typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x + y);

/**
 * ! 带领域的enum，其与C code中的enum有一些区分
 * ! 重点在于enum之后指明的关键字class
 *      ! 绝不会隐式转换 int <-> enum，这在C code中是很常见的
 *      ! 如果数值不再enumeration声明的作用域内，必须声明作用域
 *      ! 可以显示声明其低层类型，以保证获取一个大小 -> 默认类型是Int
*/

enum class Salutation: char {
    mr,
    ms,
    co,
    none,
};

void func(Salutation salutation) {
    switch (salutation)
    {
    case Salutation::mr:
        break;
    case Salutation::ms:
        break;
    default:
        break;
    }           
}

// ? 默认参数
template <typename T, typename container = std::vector<T>>
class MyClass {
    // ! typename也可以用来阐明紧随其后的是一个类型
    typename T::SubType * ptr;
    // ! 比如有可能T是一个类，而其中有一个 typedef int SubType
};

int main() {
    print(7.5, "hello", std::bitset<16>(377), 42);
    // ? lambda函数
    [] { std::cout << "hello lambda" << std::endl; } ();
    // ! 注意的是，lambda不可以是template，始终必须指明所有类型
    auto l = [](const std::string& str) {
        std::cout << str << std::endl;
    };
    l("hello world");

    auto p = returnLambda();
    std::cout << p(6, 7) << std::endl;
    return 0;
}