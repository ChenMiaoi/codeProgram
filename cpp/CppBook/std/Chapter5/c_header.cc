#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstring>

/**
 * ! cstddef内的定义
 * ! NULL、nullptr_t、size_t
 * ! ptrdiff_t，一种正负号类型，表示指针之间的距离
 * ! max_align_t 所有环境的最大对齐位，针对所有类型
 * ! offsetof 表示成员在某个struct或union中的偏移量
 * */

struct A {
    int a;
    int b;
    double d;
};

union B {
    int a;
    char c;
};

void foo() {
    int arr[3] = {0, 1, 3};
    ptrdiff_t dif = arr + 2 - arr;
    std::cout << dif << std::endl;

    std::cout << "struct A d: " << offsetof(A, d) << std::endl;
    B a;
    a.a = 20;
    std::cout << "union B c: " << offsetof(B, a) << std::endl;
}

/**
 * ! cstdlib
 * ! EXIT_SUCCESS 、EXIT_FAILURE表示程序正常、非正常结束
 * ! exit(int status)，退出程序，并清理static对象
 * ! quick_exit(int status) 自C++11，退出程序时以at_quick_exit()清理
 * ! _Exit(int status) 退出程序而不清理
 * ! abort() 退出程序(可能导致崩溃)
 * ! atexit(void (*func)()) 退出程序时调用func
 * ! at_quick_exit(void (*func)()) 在quick_exit上调用func
 * */

void foo1() {
    // ! 经由atexit()注册的函数，在程序正常退出时会依注册的相反次序被一一调用
    // ! exit()会销毁所有static对象，清空所有缓冲区，关闭所有I/O通道，然后终止程序，而终止前，会调用atexit()注册的程序
    // ! 如果atexit()抛出异常，则会调用terminate()
    // ! 而quick_exit()会调用at_quick_exit()和_Exit()，因此，该函数不会清理
    // ! 而abort()则调用terminate()
    exit(EXIT_FAILURE);
    quick_exit(EXIT_SUCCESS);
}

/**
 * ! cstring
 * ! @brief memchr(const void* ptr, int c, size_t len) 在ptr所指的前len个byte中找出字符c
 * ! @brief memcmp(const void* ptr1, const void* ptr2, size_t len) 比较ptr1和ptr2的前len个byte
 * ! @brief memcpy(void* toPtr, const void* fromPtr, size_t len) 将fromPtr的前len个byte复制至toPtr
 * ! @brief memmove(void* toPtr, const void* fromPtr, size_t len) 将fromPtr的前len个byte复制至toPtr
 * ! @brief memset(void* ptr, int c, size_t len) 将ptr所指的前len个byte赋值为字符c
 * */

void foo2() {
    const char* str = "hello world";
    auto ref = memchr(str, 'o', 5);
    std::cout << ref << std::endl;
    std::cout << memcmp(str, "hello", 5) << std::endl;
    char arr[] = "hello world";
    memcpy(arr, "cpp", 3);
    std::cout << arr << std::endl;
    memmove(arr, "hel", 3);
    std::cout << arr << std::endl;
    char arr1[5];
    memset(arr1, 'h', 4);
    arr1[4] = '\0';
    std::cout << arr1 << std::endl;
}

int main() {
    foo();
    atexit([](){ std::cout << "atexit -> func" << std::endl;});
    at_quick_exit([](){ std::cout << "at_quick_exit -> func" << std::endl;});
    std::cout << "normal running" << std::endl;
    // foo1();
    foo2();
    return 0;
}