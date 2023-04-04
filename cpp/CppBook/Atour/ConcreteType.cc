#include <iostream>
#include <vector>
#include "Vector/Vector.h"

class complex {
public:
    complex(double re, double im): _re {re}, _im {im} {}
    complex(double re): _re {re}, _im {0} {}
    complex(): _re {0}, _im {0} {}
    complex(const complex& z): _re {z._re}, _im {z._im} {}
public:
    double real() const { return _re; }
    double imag() const { return _im; }
    void real(double re) { _re = re; }
    void imag(double im) { _im = im; }
public:
    complex& operator+= (complex z) {
        _re += z._re;
        _im += z._im;
        return *this;
    }
    complex& operator-= (complex z) {
        _re -= z._re;
        _im -= z._im;
        return *this;
    }
    complex& operator*= (complex z);
    complex& operator/= (complex z);
    complex operator+ (complex z) {
        complex temp = *this;
        return temp += z;
    }
    complex operator- (complex z) {
        complex temp = *this;
        return temp -= z;
    }
    complex operator* (complex z) {
        complex temp = *this;
        return temp *= z;
    }
    complex operator/ (complex z) {
        complex temp = *this;
        return temp /= z;
    }
    bool operator== (complex z) { return this->real() == z.real() && this->imag() == z.imag(); }
    bool operator!= (complex z) { return !(*this == z); }
private:
    double _re;
    double _im;
};

class Container {
public:
    virtual double& operator[] (int) = 0; // pure virtual function
    virtual auto size() -> int const = 0; // const member function
    virtual ~Container() {} // destructor
};

class Vector_container: public Container { // Vector_container implements
public:
    Vector_container(int s): v(s) {} // Vector of s elements Container
    ~Vector_container() {}

    double& operator[] (int i) override { return v[i]; }
    auto size() -> int const override { return v.size(); }
private:
    Vector v;
};

class Point {
public:
    double x;
    double y;
};

class Shape {
public:
    virtual Point center() const = 0; // pure virtual
    virtual void move(Point to) = 0;

    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;

    virtual  ~Shape() {}
};

class Circle: public Shape {
public:
    Circle(Point p, int rad): x {p}, r {rad} {} // constructor
    Point center() const override { return x; }
    void move(Point to) override { x = to; }
    void draw() const override;
    void rotate(int) override {}
private:
    Point x; // center
    int r; // radius
};

class Smiley: public Circle {
public:
    Smiley(Point p, int rad): Circle {p, rad}, mouth {nullptr} {}
    ~Smiley() {
        delete mouth;
        for (auto p : eyes)
            delete p;
    }

    void move(Point to) override;
    void draw() const override;
    void add_eyes(Shape* s) {
        eyes.push_back(s);
    }
    void set_mouth(Shape* s);
    virtual void wink(int  i); // wink eye number
private:
    std::vector<Shape*> eyes; // usually two eyes
    Shape* mouth;
};

void Smiley::draw() const {
    Circle::draw();
    for (auto p : eyes)
        p->draw();
    mouth->draw();
}

enum class Kind {
    circle,
    traingle,
    smiley
};

//Shape* read_shape(std::istream& is) {
//    // read shape header from is and find its Kind k ...
//    Kind k;
//    switch (k) {
//        case Kind::circle:
//            // read circle data
//            return new Circle {p, r};
//        case Kind::traingle:
//            // read traingle data {p1, p2, p3}
//            return new Traingle {p1, p2, p3};
//        case Kind::smiley:
//            // read smiley data
//            Smiley* ps = new Smiley {p, r};
//            ps->add_eyes(e1);
//            ps->add_eyes(e2);
//            ps->set_mouth(m);
//            return ps;
//    }
//}
//
//void user() {
//    std::vector<Shape*> v;
//    while (std::cin)
//        v.push_back(read_shape(std::cin));
//    draw_all(v); // call draw() for each element
//    rotate_all(v, 45); // call rotate(45) for each element
//
//    for (auto p : v)
//        delete p;
//}

int main() {

    return 0;
}