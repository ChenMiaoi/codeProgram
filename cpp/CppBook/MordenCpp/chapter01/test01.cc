#include <iostream>
#include <memory>
#include "shape_wrap.hpp"

enum class shape_type {
    circle,
    triangle,
    rectangle,
};

class shape {
public:
    shape() {
        std::cout << "class shape create!" << std::endl;
    };
    virtual ~shape() {
        std::cout << "class shape delete!" << std::endl;
    }
};

class circle: public shape {
public:
    circle() {
        std::cout << "class circle create!" << std::endl;
    }
    ~circle() {
        std::cout << "class circle delete!" << std::endl;
    }
};

class triangle: public shape {
public:
    triangle() {
        std::cout << "class triangle create!" << std::endl;
    }
    ~triangle() {
        std::cout << "class triangle delete!" << std::endl;
    }
};

class rectangle: public shape {
public:
    rectangle() {
        std::cout << "class rectangle create!" << std::endl;
    }
    ~rectangle() {
        std::cout << "class rectangle delete!" << std::endl;
    }
};

shape* create_shape(shape_type type) {
    switch (type) {
        case shape_type::circle: return new circle();
        case shape_type::triangle: return new triangle();
        case shape_type::rectangle: return new rectangle();
        default: return nullptr;
    }
}

// 已经相当于一个基础的智能指针了
class shape_wrap {
private:
    shape* _ptr;
public:
    explicit shape_wrap(shape* ptr = nullptr): _ptr(ptr) {
        std::cout << "wrap the shape" << std::endl;
    }
    ~shape_wrap() {
        delete _ptr;
        std::cout << "wrap shape deleted" << std::endl;
    }
public:
    shape* get() const { return _ptr; }
};

void test() {
    // 如果就单独这样构造，无法被delete
    // auto ptr = create_shape(shape_type::circle);
    shape_wrap ptr_wrap(create_shape(shape_type::circle));
    // std::unique_ptr<shape> ptr_shared(create_shape(shape_type::circle));
}

int main() {
    // test();
    share_wrap<shape> ptr1 {create_shape(shape_type::circle)};
    // share_wrap<shape> ptr2 {ptr1};
    share_wrap<shape> ptr3;
    ptr3 = std::move(ptr1);

    share_wrap<circle> p1(new circle());
    printf("use count of ptr1 is %ld\n", p1.use_count());
    share_wrap<circle> p2;
    printf("use count of ptr2 is %ld\n", p2.use_count());
    p2 = p1;
    printf("use count of ptr2 is %ld\n", p2.use_count());

    if (p1) {
        printf("p1 is not empty!\n");
    }
    share_wrap<circle> p3 = dynamic_pointer_cast<circle>(p2);
    printf("use count of ptr3 is %ld\n", p3.use_count());
    return 0;
}