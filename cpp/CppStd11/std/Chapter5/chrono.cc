#include <iostream>
#include <chrono>
#include <ratio>

/**
 * ! 自C++11起，提供了chrono时间库
 * ! 所谓duration(时间段)指的是在某时间单位上的一个明确的tick(片刻数)，也就是说，三分钟，实际上是三个一分钟，三个就是片刻数，而一分钟是时间单位
 * ! 所谓timepoint(时间点)指的是一个duration和一个epoch(起始点)的组合。也就是自格林威治时间到给定时间点的一个时间戳
 * */

// ! duration是一个数值(tick个数)和一个分数(表示时间单位，以秒计，且由ratio表示)的组合
void foo() {
    std::chrono::duration<int> twentySecond(20);
    std::chrono::duration<double, std::ratio<60>> halfAMinute(0.5); // ! 也就是以60 / 1s为时间单位
    // ! 实际上，chrono给出了更简便的方式
    std::chrono::minutes twoMinutes(2);
    std::chrono::hours  oneHours(1);

    // ! 同时，chrono给duration提供了很多运算关系，而common_type<>也提供了一个重载版本
    std::chrono::duration<int, std::ratio<1, 3>> d1(1);
    std::chrono::duration<int, std::ratio<1, 5>> d2(1);
    d1 + d2;
    d1 - d2;
    d1 < d2;
}

int main() {
    foo();
    return 0;
}