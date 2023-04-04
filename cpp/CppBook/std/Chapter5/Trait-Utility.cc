#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>
#include <array>

/**
 * ! C++标准库中几乎每样东西都以template为基准，为了更好的支持，在C++11中引入了Type trait，定义出因type而异的行为
 * ! 其可被用来针对type优化代码
 *
 * ? 所谓type trait就是提供一种用来处理type属性(property of a type)的办法。是一个template，可在编译期根据一或多个template实参产出一个type或value
 * */

template <typename T>
void foo(const T& var) {
    if (std::is_pointer<T>::value) { // ! is_pointer<>用于检查模板是否是pointer type,返回一个bool类型
        std::cout << "foo() called for a pointer" << std::endl;
    }else {
        std::cout << "foo() called for a value" << std::endl;
    }
}

// ! 但是，我们不允许这样做
template <typename T>
void foo1(const T& var) {
    std::cout << (std::is_pointer<T>::value ? *var : var) << std::endl;
    // ! 因为该式子是一个编译期表达式，如果传入的T是一个int时，则会变为 false ? *int : int，很显然, *int是一个无效表达式
}

// ! 但是，is_pinter<>()支持这样做
template <typename T>
void foo_impl(const T& var, std::true_type) {
    std::cout << "foo() called for pointer to " << *var << std::endl;
}
template <typename T>
void foo_impl(const T& var, std::false_type) {
    std::cout << "foo() called for value to " << var << std::endl;
}
template <typename T>
void foo2(const T& var) {
    // ! 通过is_pointer<T>()在编译期产生出true_type or false_type
    foo_impl(var, std::is_pointer<T>());
}

// ! type trait的威力，假如你需要重载int、short、float等函数，通过type trait来实现是很高效的
template <typename T>
void func_impl(T var, std::true_type) {
    std::cout << "It's integral version!" << std::endl;
}
template <typename T>
void func_impl(T var, std::false_type) {
    std::cout << "It's floating-point version!" << std::endl;
}
template <typename T>
void func(T var) {
    func_impl(var, std::is_integral<T>());
}

/**
 * ! 并且，处理两个或多个类型中的通用类型时，type trait也是很有用处的
 * */
 template <typename T1, typename T2>
 typename std::common_type<T1, T2>::type min(const T1& x, const T2& y) {
    return x < y ? x : y;
 }

 enum class A {};
 union D {};
 struct B {};
 class C {};

 void func1() {
     // ! 用于检测类型性质的trait
     std::cout << std::is_void<void>::value << "\n";
     std::cout << std::is_integral<int>::value << "\n";
     std::cout << std::is_integral<char>::value << "\n";
     std::cout << std::is_floating_point<float>::value << "\n";
     std::cout << std::is_const<const int>::value << "\n";
     std::cout << std::is_const<int* const>::value << "\n"; // ! ture
     std::cout << std::is_const<const int*>::value << "\n"; // ! false
     std::cout << std::is_array<int[3]>::value << "\n";
     std::cout << std::is_array<std::array<int, 3>>::value << "\n"; // ! false
     std::cout << std::is_enum<A>::value << "\n";
     std::cout << std::is_union<D>::value << "\n";
     std::cout << std::is_class<B>::value << "\n";
     std::cout << std::is_class<C>::value << "\n";
     std::cout << std::is_function<void (*)(int)>::value << "\n";
     std::cout << std::is_lvalue_reference<int&>::value << "\n";
     std::cout << std::is_rvalue_reference<int&&>::value << "\n";
 }

 void func2() {
     // ! 用于检验类型关系的type trait
     std::cout << std::is_same<int, long>::value << "\n";
     std::cout << std::is_convertible<int, long>::value << "\n";
     std::cout << std::is_assignable<int, long>::value << "\n";
 }

 void func3() {
     // ! 类型修饰符type trait
     // ! 为类型添加一个属性，前提是该属性尚未存在，或移除一个属性，前提是该属性已经存在
     using T = int;
     std::add_const<T>::type i = 10;
     // i = 12; // ! Error!
     std::add_lvalue_reference<const T>::type j = i;
 }

 void func4() {
     // ! 其余type trait
     std::cout << std::rank<int>::value << "\n";
     std::cout << std::rank<int[]>::value << "\n";
     std::cout << std::rank<int[5]>::value << "\n";
     std::cout << std::rank<int[][7]>::value << "\n";
     std::cout << std::rank<int[5][7]>::value << "\n";
 }

 /**
  * ! Reference Wrapper(外覆器)
  * ! 用于使用reference语义，提供ref()以传递T&，cref()以传递const T&
  * ! 常用于
  * ? 1. make_pair()创建pair<> of reference
  * ? 2. make_tuple()创建tuple<> of reference
  * ? 3. Binder绑定reference
  * ? 4. Thread传递reference
  * */

 template <typename T>
 void foo4(T var) {
     if (std::is_reference<T>::value)
         std::cout << "the reference version" << std::endl;
     std::cout << "the value version" << std::endl;
     // ! 而且，STL容器元素也适用
     std::vector<std::reference_wrapper<std::string>> coll;
 }

 /**
  * ! Function Type Wrapper(外覆器)
  * ! class std::function<>提供多态外覆器，能够允许把可调用对象(callable object)当做最高级对象
  * */

 class E {
 public:
     int add(int x, int y) {
         return x + y;
     }
 };
 int add(int x, int y) {
     return x + y;
 }

 void foo5() {
     std::vector<std::function<int(int, int)>> tasks;
     tasks.push_back(add);
     tasks.push_back([](int x, int y) -> int {
        return x + y;
     });
     std::cout << tasks[0](1, 2) << "\n";
     std::cout << tasks[1](1, 2) << "\n";
 }

int main() {
    int a = 1;
    foo(&a);
    foo2(a);
    func<int>(5);
    func<long long>(6L);
    func<double>(6.5);
    std::cout << min(12, 5.65) << std::endl;
    func1();
    func2();
    func3();
    func4();
    int x = 5;
    foo4(std::ref(x));
    foo5();
    return 0;
}