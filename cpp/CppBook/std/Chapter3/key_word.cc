#include <iostream>
#include <array>
#include <limits>

/**
 * noexcept瞄准了空异常明细
 *      运行期检查：C++异常明细是在运行期被检查，因此运行期失败的处理再调用std::unexpected()为时已晚
 *      运行期开销：运行期检查会导致编译器产生额外代码且阻碍优化的进行
 *      无法用于泛型：泛型中往往不知道哪一种异常被抛出
 * */

void foo() noexcept {
    // 如果在noexcept中仍然抛出异常，则会终止程序
    throw std::bad_array_new_length();
}

/**
 * noexcept(...)可以指定一个条件，而noexcept = noexcept(true)这一条件
 * */
template <typename Type>
void _swap(Type& x, Type& y) noexcept(noexcept(x._swap(y))) {
    x._swap(y);
}

/**
 * 每一个库函数，它们，不可抛出异常且未指明任何不明确(未定义)行为，应被标识为无条件的noexcept
 * 如果是程序库提供的swap函数，move construction or move assignment operator 可借由noexcept操作符证明不抛出异常
 * 且应该标识为带条件的noexcept，任何其他函数都不应该使用待条件的except
 * 程序库的任何析构函数都不允许抛出异常，且必须使用隐式的nonthrowing异常明细
 * 如果程序库函数用来与C code兼容，则可使用无条件的noexcept
 * */

/**
 * C++11起，constexpr可用来让表达式核定于编译期
 * */

constexpr int square(int x) {
    return x * x;
}

/**
 * 该关键字修正了一个数值极限的问题，在C中宏INT_MAX是常量替换
 * 而C++98中，std::numeric_limits<short>::max()则不是一个常量，但C++11后使用constexpr即为常量表达式
 * */

std::array<char, std::numeric_limits<char>::max()> a;

int main() {
    float a[square(9)]; // OK, 因为square现在是一个常量表达式
    return 0;
}