#include <complex>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace std {
    template <typename T>
    struct hash<complex<T>> {
        size_t
        operator() (const complex<T>& v) const noexcept {
            hash<T> h;
            return h(v.real()) + h(v.imag());
        }
    };
}

int main() {
    std::unordered_set<int> s {
        1, 1, 2, 3, 5, 8, 13, 21
    };
    for (const auto i : s) std::cout << i << " ";
    std::cout << "\n";

    std::unordered_map<std::complex<double>, double> umc {
            { {1.0, 1.0}, 1.4142 },
            { {3.0, 4.0}, 5.0 },
    };
    for (const auto i : umc) std::cout << i.first << " => " << i.second << "\n";
}