#include <iostream>
#include <ostream>
#include <iomanip>
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

template <typename V, typename R>
std::ostream& operator<< (std::ostream& _out, const std::chrono::duration<V, R>& d) {
    // ! count()就是有多少个ticks
    _out << "[" << d.count() << " of " << R::num << "/" << R::den << "]";
    return _out;
}

void foo1() {
    std::chrono::milliseconds d(42);
    std::cout << d << std::endl;

    // ! 我们可以通过duration_cast<>()强制转换类型
    std::chrono::seconds sec(55);
    // ! std::chrono::minutes m1 = sec; ERROR!
    // ! 但是这样会丢失精度
    std::chrono::minutes m1 = std::chrono::duration_cast<std::chrono::minutes>(sec);
    std::cout << m1 << std::endl;
}

/**
 * ! clock定义处一个epoch(起始点)和一个tick周期，此外，clock还提供一个类型给"与此clock关联"的任何timepoint使用
 * ! 并且，clock提供一个now()来获取"现在时刻"的timepoint对象
 *
 * ! timepoint表现出某个特定时间点，关联至某个clock的某个正值或负值duration，timepoint提供产出epoch，产出"与其clock相应"
 * ! 的所有timepoint中的最大值和最小值，以及timepoint的各种算数运算
 *
 * ! C++11提供了三种clock，每一个都具备大致相同的接口
 * ! system_clock，所表现的timepoint将关联至现行操作系统的即时时钟，且提供to_time_t()、from_time_t()允许在timepoint和C的系统时间
 * ! time_t中转换
 * ! steady_clock，保证绝不会被调整，因此实际时间流逝，其timepoint值绝不会减少
 * ! high_resolution_clock, 表现的是当前系统带有最短tick周期的clock
 * */

template <typename C>
void printClockData() {
    std::cout << "- precision: ";
    using P = typename C::period; // ! 获取时间单位类型
    if (std::ratio_less_equal<P, std::milli>::value) { // ! 转换为milliseconds
        using TT = typename std::ratio_multiply<P, std::kilo>::type;
        std::cout << std::fixed << double (TT::num) / TT::den << " milliseconds" << std::endl;
    }else {
        // ! 以seconds打印
        std::cout << std::fixed << double (P::num) / P::den << " seconds" << std::endl;
    }
    std::cout << "- is_steady: " << std::boolalpha << C::is_steady << std::endl;
}

void foo2() {
    std::cout << "system_clock: " << std::endl;
    printClockData<std::chrono::system_clock>();
    std::cout << "\nhigh_resolution_clock: " << std::endl;
    printClockData<std::chrono::high_resolution_clock>();
    std::cout << "\nsteady_clock: " << std::endl;
    printClockData<std::chrono::steady_clock>();

    auto system_start = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 10000>>>(std::chrono::system_clock::now() - system_start);
    std::cout << diff << std::endl;
}

int main() {
    foo();
    foo1();
    foo2();
    return 0;
}