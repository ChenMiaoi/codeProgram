#include <iostream>
#include <ratio>

// ! C++11起，C++标准库提供了一个接口允许你具体指定编译期分数，并且允许对它进行编译期运算
// ! 也就是说，在ratio中，传递的分子分母自动化为最简式

void foo() {
    using FiveThirds = std::ratio<5, 3>;
    std::cout << FiveThirds ::num << "/" << FiveThirds::den << "\n";
    using AlsoFiveThirds = std::ratio<25, 15>;
    std::cout << AlsoFiveThirds::num << "/" << AlsoFiveThirds::den << "\n";
}

/**
 * ! ratio定义了四种基本运算，以及各种比较符
 * */

void foo1() {
    std::cout << std::ratio_add<std::ratio<1, 5>, std::ratio<4, 9>>::num << "/"
              << std::ratio_add<std::ratio<1, 5>, std::ratio<4, 9>>::den << "\n";
    std::cout << std::ratio_subtract<std::ratio<1, 5>, std::ratio<4, 9>>::num << "/"
              << std::ratio_subtract<std::ratio<1, 5>, std::ratio<4, 9>>::den << "\n";
    std::cout << std::ratio_multiply<std::ratio<1, 5>, std::ratio<4, 9>>::num << "/"
              << std::ratio_multiply<std::ratio<1, 5>, std::ratio<4, 9>>::den << "\n";
    std::cout << std::ratio_divide<std::ratio<1, 5>, std::ratio<4, 9>>::num << "/"
              << std::ratio_divide<std::ratio<1, 5>, std::ratio<4, 9>>::den << "\n";

    std::cout << std::ratio_equal<std::ratio<5, 3>, std::ratio<25, 15>>::value << "\n";
    std::cout << std::ratio_not_equal<std::ratio<5, 3>, std::ratio<25, 15>>::value << "\n";
    std::cout << std::ratio_less<std::ratio<5, 3>, std::ratio<25, 15>>::value << "\n";
    std::cout << std::ratio_greater<std::ratio<5, 3>, std::ratio<25, 15>>::value << "\n";
}

int main() {
    foo();
    foo1();
    return 0;
}