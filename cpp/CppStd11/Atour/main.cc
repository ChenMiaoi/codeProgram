#include <iostream>
#include <set>
#include <chrono>

// for the " ' ";
void test() {
    double x = 3.1415'9265'4646;
    double x1 = 0x7546'ddde'45;
    double x2 = 04657'123;
    double x3 = 0b0101'1100'1101;
}

void function(int* a, int& b) {
    // if we not use const to limit pointer and reference, the data may be modified
    *a = 5;
    b = 6;
}

void function(const int* a, const int& b) {
    // if we use const, when we may modify it careless, const will talk to the compiler, we don't want it modified
    // *a = 6; wrong
    // b = 7; wrong
}

void Constants() {
    // if we use const, we can do pass data without fear of it being modified
    int a = 2, b = 3;
    function(&a, b);
}

constexpr long fibonacii(long num) {
    return num <= 2 ? 1 : fibonacii(num - 1) + fibonacii(num - 2);
}

long fibonacii(long num, int) {
    return num <= 2 ? 1 : fibonacii(num - 1) + fibonacii(num - 2);
}

void Constants(int) {
    std::chrono::time_point start = std::chrono::system_clock::now();
    std::cout << fibonacii(45) << "\n";
    std::chrono::time_point end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << " milliseconds -> constexpr\n";

    start = std::chrono::system_clock::now();
    std::cout << fibonacii(45, 0) << "\n";
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << " milliseconds -> none\n";
}

consteval double nth(double x, int n) {
    double res = 1;
    int i = 0;
    while (i < n) {
        res *= x;
        ++i;
    }
    return res;
}

int main() {

    return 0;
}