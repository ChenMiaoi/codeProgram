#include <iostream>
#include <memory>
#include <future>
#include <functional>

/**
 * ! C++在不同地方都用了术语callable object，意思是 可被某种方式调用其某些函数的对象
 *      ! 一个函数，接受额外传入args作为实参 argument
 *      ! 一个指向成员函数的指针，当你调用他时，该对象被传递称为第一实参，其他实参则是一一对应成员函数的参数
 *      ! 一个函数对象，且拥有operator()
 *      ! 一个lambda
*/

void func(int x, int y);

auto l = [](int x, int y) {};

class C {
public:
    void operator() (int x, int y) const ;
    void memfunc(int x, int y) const ;
};

int main() {
    C c;
    std::shared_ptr<C> sp(new C);
    // ? use bind()
    std::bind(func, 77, 33); // ? calls: func(77, 33)
    std::bind(l, 77, 33); // ? calls: l(77, 33)
    std::bind(C(), 77, 33); // ? calls: C.operator()(77, 33)
    std::bind(&C::memfunc, c, 77, 33); // ? calls: c.memfunc(77, 33)
    std::bind(&C::memfunc, sp, 77, 33); // ? calls: sp->memfunc(77, 33)

    // ? use async() 异步
    std::async(func, 77, 33); // ? calls: func(77, 33)
    std::async(l, 77, 33); // ? calls: l(77, 33)
    std::async(c, 77, 33); // ? calls: C.operator()(77, 33)
    std::async(&C::memfunc, &c, 77, 33); // ? calls: c.memfunc(77, 33)
    std::async(&C::memfunc, sp, 77, 33); // ? calls: sp->memfunc(77, 33)
    return 0;
}