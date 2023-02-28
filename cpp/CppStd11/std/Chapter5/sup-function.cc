#include <iostream>
#include <algorithm>
#include <utility>

/**
 * ! 最大值和最小值
 * ! min(a, b)、min(a, b. cmp)、min(initlist)、min(initlist, cmp)
 * ! max与min一致，且注意，双实参版本返回的是一个引用
 * ! minmax(a, b)、minmax(a, b, cmp)、minmax(initlist)、minmax(initlist, cmp)
 * ! 该版本返回一个最大值和最小值的pair，当然，双实参版本依旧是引用
 * */

void foo() {
    int x = 2, y = 7;
    std::cout << std::min(x, y) << "\n";
    std::cout << *std::min(&x, &y) << "\n";
    std::cout << *std::min(&x, &y, [](int* x, int* y) {return *x > *y;}) << "\n";
    std::cout << std::min({x, y}) << "\n";
    std::cout << std::min({x, y}, [](int x, int y) {return x > y;}) << "\n";

    // ! max与上述一致

    std::cout << std::minmax(x, y).first << " : " << std::minmax(x, y).second << "\n";
    std::cout << std::minmax(x, y, [](int x, int y){return x < y;}).first << " : "
              << std::minmax(x, y, [](int x, int y){return x < y;}).second << "\n";
    std::cout << std::minmax({x, y}).first << " : " << std::minmax({x, y}).second << "\n";
    std::cout << std::minmax({x, y}, [](int x, int y){return x < y;}).first << " : "
              << std::minmax({x, y}, [](int x, int y){return x < y;}).second << "\n";
}

/**
 * ! 两值互换
 * ！ 自C++11起，swap重载了右值引用，并且提供了一个针对array的版本
 * */

class MyContainer {
public:
    void swap(MyContainer& x) {
        std::swap(elems, x.elems);
        std::swap(numElems, x.numElems);
    }
private:
    int* elems;
    int numElems;
};

inline void swap(MyContainer& c1, MyContainer& c2) noexcept(noexcept(c1.swap(c2))) {
    c1.swap(c2);
}

/**
 * ! 增补的比较运算符
 * ! 在C++11中，有四个function template分别定义了!=、>=、<=、>这四个操作，其都是利用==和<来完成的
 * ! 因此，在类中，我们只需要完成<和==
 * */

class X {
public:
    bool operator== (const X& x) const {
        return a == x.a;
    }
    bool operator< (const X& x) const {
        return a < x.a;
    }
private:
    int a;
};

void foo1() {
    // ! 使用namespace std::rel_ops即可自动完成其余四个比较运算
    using namespace std::rel_ops;
    X x1, x2;
    if (x1 != x2) {}
    if (x1 > x2) {}
    if (x1 <= x2) {}
    if (x1 >= x2) {}
}

// ! 但是，如果你这样做了，就必须付出可移植性的代价

int main() {
    foo();
    foo1();
    return 0;
}