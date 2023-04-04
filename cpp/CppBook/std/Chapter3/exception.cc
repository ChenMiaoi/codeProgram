#include <iostream>
#include <vector>
#include <bitset>
#include <exception>

/**
 * ! 实际上，自C++11起，已不再推荐使用异常明细
*/

// ? Logic Error异常类
/**
 * ! 针对逻辑异常总是派生于logic_error
 * ! invalid_argument表示无效实参，比如将bitset以char而非0或1初始化
 * ! length_of_range指出某个行为可能超出最大容量
 * ! out_of_range指出实参值不在预期之内
 * ! domain_error指出领域范畴内的错误
*/

void func(std::vector<int>& v, int pos) {
    if (pos >= v.size())
        throw new std::out_of_range("out of range");
}

/**
 * ? Runtime Error异常类
 * ! range_error指出内存计算时发生的区间错误，常见于wide string 和 byte string之间的转换
 * ! overflow_error指出算术运算上溢
 * ! underflow_error指出算术运算发生下溢
 * ! system_error指出因底层操作系统而发生的错误，其是自C++11起规定的
 * ! bad_alloc只要全局new失败，就会抛出该异常
*/

// ! 成员函数what() -> 自定义异常类
// ! 对于所有的标准异常，用于获取类型以外的附加信息的唯一成员函数就是what()

class MyException: std::exception {
public:
    const char* what() const noexcept {
        return "My Exception";
    }
};

int main() {
    std::vector<int> v(5);
    try {  
        func(v, 6);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}