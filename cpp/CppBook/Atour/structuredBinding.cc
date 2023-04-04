#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <type_traits>

struct Entry {
    std::string name;
    int value;
};

auto read_entry(std::istream& is) -> Entry {
    std::string str;
    int i;
    is >> str >> i;
    return {str, i};
}

auto incr(std::map<std::string, int>& m) {
    for (auto& [key, value] : m) {
        ++value;
    }
}

template <typename T>
class complex;

template<>
class std::tuple_size<complex<double>>
    : public std::integral_constant<size_t, 2> {};

template <>
class std::tuple_element<0, complex<double>> {
public:
    using type = double;
};

template <>
class std::tuple_element<1, complex<double>> {
public:
    using type = double;
};

template <typename T>
struct complex {
    complex(T _re, T _im): re {_re}, im {_im} {}
    complex<T>& operator+ (T d) {
        this->re += d;
        return *this;
    }
public:
    template<size_t Index>
    std::tuple_element_t<Index, complex<double>> &get() &;
private:
    T re;
    T im;
};

template<> template <>
std::tuple_element_t<0, complex<double>> &complex<double>::get<0>() & {
    return re;
}

template <> template <>
std::tuple_element_t<1, complex<double>> &complex<double>::get<1>() & {
    return im;
}

int main() {
    complex<double> z = {1, 2};
    auto& [re, im] = z + 2;
    std::cout << re << " " << im << "\n";
    //    auto [str, _] = read_entry(std::cin);
    //    _ = 5;
    //    std::cout << str;
    return 0;
}