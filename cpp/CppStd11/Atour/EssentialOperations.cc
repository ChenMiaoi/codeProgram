#include <iostream>
#include <string>
#include "Operation-Vector//Vector.h"

template <typename Sometype>
class X {
public:
    X(Sometype) { std::cout << "X(Sometype)" << "\n"; }; // "ordinary constructor": create an object
    X() { std::cout << "X()" << "\n"; }; // default constructor
    X(const X&) { std::cout << "X(const X&)" << "\n"; }; // copy constructor
    X(X&&) { std::cout << "X(X&&)" << "\n"; }; // move constructor

    X<Sometype>& operator= (const X<Sometype>&) { // copy assignment: clean up target and copy
        std::cout << "X& operator= (const X&)" << "\n";
        return *this;
    };
    X<Sometype>& operator= (X<Sometype>&&) { // move assignment: clean up target and move
        std::cout << "X& operator= (X&&)" << "\n";
        return *this;
    };
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

X<int> f() {
    X<int> x(1000);
    X<int> y(1000);
    X<int> z(1000);
    z = x;
    y = std::move(x);

    // return std::move(z);
    return z;
}

int main() {
    X<int> x = f();
    return 0;
}