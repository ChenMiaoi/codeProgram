import Vector;
import vector_printer;
#include <cmath>

double sqrt_sum(const Vector& v) {
    double sum = 0;
    for (int i = 0; i != v.size(); i++)
        sum += std::sqrt(v[i]);
    return sum;
}

int main() {
    Vector v(5);
    sqrt_sum(v);
    return 0;
}