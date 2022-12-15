#ifndef CPPSTD11_VECTOR_H
#define CPPSTD11_VECTOR_H

class Vector {
public:
    Vector(int s);
    double& operator[] (int i);
    int size();
private:
    double* elem;
    int sz;
};

#endif //CPPSTD11_VECTOR_H
