#ifndef CPPSTD11_VECTOR_H
#define CPPSTD11_VECTOR_H

struct Vector_size_mismatch {

};

class Vector {
public:
    Vector() {}
    Vector(int s); // constructor: establish invariant, acquire resources
    ~Vector() { delete[] elem; } // destructor: release resources

    Vector(const Vector& a); // copy constructor
    Vector& operator= (const Vector& a); // copy assignment
    Vector operator+ (const Vector& a);

    double& operator[] (int i);
    const double& operator[] (int i) const;

    int size() const;
private:
    double* elem; // elem points to an array of sz doubles
    int sz;
};

#endif //CPPSTD11_VECTOR_H
