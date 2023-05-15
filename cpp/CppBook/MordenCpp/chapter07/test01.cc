#include <iostream>
#include <string>
#include <complex>
#include <thread>
#include <map>

template <typename T>
class Obj {
public:
    Obj(T value);
};

Obj(const char*) -> Obj<std::string>;

auto test() -> void {
    std::multimap<std::string, int> m { {"four", 4} };
    std::multimap<std::string, int>::iterator lower, upper;
    std::tie(lower, upper) = m.equal_range("four");
    auto [l, u] = m.equal_range("four");
}

auto test1() -> void {
    using namespace std::literals::complex_literals;
    using namespace std::literals::chrono_literals;
    using namespace std::literals::string_literals;
    std::cout << "i * i = " << 1i * 1i << std::endl;
    std::cout << "waiting for 500ms" << std::endl;
    std::this_thread::sleep_for(500ms);
    std::cout << "Hello world"s.substr(0, 5) << std::endl;
}

struct length {
    double value;
    enum unit {
        metre,
        kilometre,
        millimetre,
        centimetre,
        inch,
        foot,
        yard,
        mile,
    };
    static constexpr double factors[] = {
            1.0, 1000.0, 1e-3,
            1e-2, 0.0254, 0.3048,
            0.9144, 1609.344,
    };
    explicit length(double v, unit u = metre): value(v * factors[u]) {}

};

length operator+ (length lhs, length rhs) { return length{lhs.value + rhs.value}; }
length operator"" _m(long double v) { return length (v, length::metre); }
length operator"" _cm(long double v) { return length (v, length::centimetre); }


int main() {
    test1();
    return 0;
}