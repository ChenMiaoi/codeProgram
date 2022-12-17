#include <iostream>
#include <vector>
export module vector_printer;

export template <typename T>
void print(std::vector<T>& v) { // this is the (only) function seen by users
    std::cout << "{\n";
    for (const T& val : v) {
        std::cout << " " << val << "\n";
    }
    std::cout << "}";
}