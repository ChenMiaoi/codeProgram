#include <iostream>
#include <string>
#include <chrono>
#include <complex>
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

class Matrix {
public:
    Matrix& operator= (const Matrix& matrix); // assign m to *this; return a reference
    // Matrix operator+ (const Matrix& matrix);
};

Matrix operator+ (const Matrix& matrix1, const Matrix& matrix2);

//class R {
//    auto operator<=> (const R& a) const = default;
//};
//
//void user(const R& r1, const R& r2) {
//    bool b1 = (r1 <=> r2) == 0; // r1 == r2;
//    bool b2 = (r1 <=> r2) < 0; // r1 < r2;
//    bool b3 = (r1 <=> r2) > 0; // r1 > r2;
//
//    bool b4 = (r1 == r2);
//    bool b5 = (r1 < r2);
//}

constexpr std::complex<long double> operator""_i (long double arg) {
    return {0, arg};
}

constexpr std::chrono::duration<int> operator""_h (unsigned long long hour) {
    return {};
}

int main() {
    X<int> x = f();
    std::string str = "hello";
    using namespace std::literals::string_literals;
    std::string str_s = "hello"s;
    using namespace std::literals::chrono_literals;
    std::chrono::duration time = 12h-5min-3s;
    return 0;
}