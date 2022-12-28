#include <iostream>
#include <string>
#include "Vector/Vector.h"

template <typename Sometype>
class X {
public:
    X(Sometype) { std::cout << "X(Sometype)" << "\n"; }; // "ordinary constructor": create an object
    X() { std::cout << "X()" << "\n"; }; // default constructor
    X(const X&) { std::cout << "X(const X&)" << "\n"; }; // copy constructor
    X(X&&) { std::cout << "X(X&&)" << "\n"; }; // move constructor

    X& operator= (const X&) { std::cout << "X& operator= (const X&)" << "\n"; }; // copy assignment: clean up target and copy
    X& operator= (X&&) { std::cout << "X& operator= (X&&)" << "\n"; }; // move assignment: clean up target and move
    ~X() {}; // destructor: clean up
};

template <typename Sometype>
class Y {
public:
    Y(Sometype);
    Y(const Y&) = default; // I really do want the default copy constructor
    Y(Y&&) = default; // and the default move constructor
};

struct Z {
    Vector v;
    std::string s;
};

int main() {
    Z z1;
    Z z2 = z1;
    return 0;
}