#include "Vector.h"

Vector::Vector(const Vector &a)
    : elem { new double[a.size()]}
    , sz {a.size()} {
    for (int i = 0; i != sz; i++)
        elem[i] = a.elem[i];
}

Vector::Vector(int s): elem {new double[s] } {}

Vector &Vector::operator=(const Vector &a) {
    double* p = new double[a.size()];
    for (int i = 0; i != a.size(); i++)
        p[i] = a.elem[i];
    delete[] elem; // delete old element
    elem = p;
    sz = a.size();
    return *this;
}

Vector Vector::operator+(const Vector &a) {
    if (this->size() != a.size())
        throw Vector_size_mismatch {};
    Vector res(a.size());
    for (int i = 0; i != a.size(); i++)
        // res[i] = this->operator[](i) + a[i];
         res[i] = (*this)[i] + a[i];
    return res;
}

const double &Vector::operator[](int i) const {
    return elem[i];
}

double &Vector::operator[](int i) {
    return elem[i];
}

int Vector::size() const {
    return sz;
}