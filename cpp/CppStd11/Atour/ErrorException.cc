#include "Vector/Vector.h"

void f(Vector& v) {
    try { // out_of_range exception thrown in this block are handle by the handle define below
        // computer 1... might try to access beyond the end of v
        double a = v[7]; // might try to access beyond the end of v
        // computer 2... might try to access beyond the end of v
    }catch (const std::out_of_range& exception) {
        std::cerr << exception.what() << "\n";
    }
}

void test(int n) {
    try {
        Vector v(n);
    }catch (const std::length_error& exception) {
        std::cerr << exception.what();
    }catch (const std::bad_alloc& exception) {
        std::cerr << exception.what();
    }
}

int main() {
    Vector v(5);
    // f(v);
    test(-27); // throws length_error (-27 is too small)
    test(10'0000'0000); // may throw bad_alloc
    test(10); // likely OK
    return 0;
}