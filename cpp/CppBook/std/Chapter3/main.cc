#include <iostream>
#include <utility>
#include <set>

template <typename T>
void printElements(const T& coll) {
    for (const auto& elem : coll) {
        std::cout << elem << std::endl;
    }
    // 类似于
    {
        for (auto _pos = coll.begin(); _pos != coll.end(); _pos++) {
            const auto & elem = *_pos;
            std::cout << elem << std::endl;
        }
    }
}

void func1() {
    int array[] = {1, 2, 3, 4, 5};
    long sum = 0;
    for (int x : array)
        sum += x;
    {
        for (auto elem : {sum, sum * 2, sum * 4})
            std::cout << elem << std::endl;
    }
}

template <typename X>
void createAndInsert(std::set<X>& coll) {
    X x;
    coll.insert(x); // 使用copy construction
    // 在C++11以前，使用copy construction， 但是x + x这一表达式显然是不再重复需要的
    // 拷贝一份过于冗余，因此在C++11中，出现了第二个版本的insert
    // insert(T&& v)
    coll.insert(x + x);
    coll.insert(std::move(x)); // 手动调用move construction
}

/**
 * 1. 如果你只实现了：void foo(X&);
 *      其行为如同C++98
 * 2. 如果你只实现了：void foo(const X&);
 *      其行为如同C++98，但是rvalue也会被调用，因为const & == &&
 * 3. 如果你实现了：
 *      void foo(X&); void foo(X&&); 或者
 *      void foo(const X&); void foo(X&&);
 *      其行为则是C++11，可以区分copy和move的准确行为，X&&专为rvalue所服务
 * 4. 如果你只实现了：void foo(X&&);
 *      其行为是C++11，但仅可支持rvalue的调用，如果使用lvalue行为是不允许的
 * */

class X {
public:
    X () = default;
    X (const X& lvalue); // copy construction
    X (X&& rvalue); // move construction

    X& operator= (const X& lvalue); // copy assignment operator
    X& operator= (X&& rvalue); // move assignment operator
};

/**
 * 你不应该返回一个std::move，也不需要这样做
 *  -- 如果X有一个可取用的copy or move construction，编译器可以选择省略其中的copy construction
 *  -- 这就是所谓的(named) return value optimization ((N)RVO)
 *  or，如果X有一个move construction，X会被moved
 *  or，如果X有一个copy construction，X会被copied
 *  or，报出一个编译期错误 (compile-time error)
 *
 *  -- 但是，如果返回了一个local nonstatic对象，则返回其rvalue是不对的，因为其指向会被清除
 * */

X foo() {
    X x;
    return x;
}

// X&& foo() {
//    X x;
//    return x;
//}

int main() {
    func1();
    return 0;
}