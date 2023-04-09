#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<int> v { 13, 6, 4, 11, 29 };
    for (const auto i : v) std::cout << i << " ";
    std::cout << "\n";

    std::sort(v.begin(), v.end());
    for (const auto i : v) std::cout << i << " ";
    std::cout << "\n";

    std::sort(v.begin(), v.end(), std::greater<int>());
    for (const auto i : v) std::cout << i << " ";
    std::cout << "\n";

    std::cout << std::hex;
    auto hp = std::hash<int*>();
    std::cout << "hash(nullptr) = " << hp(nullptr) << std::endl;
    std::cout << "hash(v.data()) = " << hp(v.data()) << std::endl;
    std::cout << "v.data() = " << static_cast<void*>(v.data()) << std::endl;

    auto hs = std::hash<std::string>();
    std::cout << "hash(\"hello\") = " << hs(std::string("hello")) << std::endl;
    std::cout << "hash(\"hellp\") = " << hs(std::string("hellp")) << std::endl;
    return 0;
}