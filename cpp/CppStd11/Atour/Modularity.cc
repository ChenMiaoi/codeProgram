#include <iostream>

double sqrt(double); // the square root function takes a double and returns a double

#if old_version
class Vector { // what is needed to use a Vector
public:
    Vector(int s);
    double& operator[] (int i);
    int size();
private:
    double* elem;
    int sz;
};

double sqrt(double d) { // definition of sqrt()
    // ...
    return 0;
}

Vector::Vector(int s): elem {new double[s]}, sz {s} { // definition of the constructor
    // initialize members
}

double& Vector::operator[](int i) { // definition of subscription
    return elem[i];
}

int Vector::size() { // definition of size()
    return sz;
}
#endif // old_version

int main() {

    return 0;
}