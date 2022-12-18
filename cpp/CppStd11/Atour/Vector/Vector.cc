#include "Vector.h"

Vector::Vector(int s) {
    if (s < 0)
        throw std::length_error {"Vector constructor: negative size"};
    if ((elem = new double[s]) == nullptr)
        throw std::bad_alloc {};
    sz = s;
}

double &Vector::operator[](int i) {
    if (!(0 < i && i < size()))
        throw std::out_of_range {"Vector::operaor[]()"};
    return elem[i];
}

int Vector::size() {
    return sz;
}