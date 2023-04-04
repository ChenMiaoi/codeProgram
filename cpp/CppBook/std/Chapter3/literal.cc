#include <iostream>
#include <string>

int main() {
    auto i = R"nc(
        a\b\nc()"
        )nc";
    std::cout << i << std::endl;

    auto i1 = u8"UTF-8 string literal -> const char";
    auto i2 = u"char16_t string literal";
    auto i3 = U"char32_t string literal";
    auto i4 = L"wchar_t string literal";
    return 0;
}