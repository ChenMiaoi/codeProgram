#include <iostream>
#include <limits>

int main() {
    std::cout << std::numeric_limits<char>::max() << std::endl;
    std::cout << std::numeric_limits<short>::max() << std::endl;
    std::cout << std::numeric_limits<int>::max() << std::endl;
    std::cout << std::numeric_limits<long>::max() << std::endl;
    std::cout << std::numeric_limits<float>::max() << std::endl;
    std::cout << std::numeric_limits<double>::max() << std::endl;
    return 0;
}