#include <iostream>
#include <functional>
#include <utility>
#include <complex>
#include <vector>
#include <tuple>

/**
 * ! tuple扩展了pair的概念，使其可以拥有任意数量的元素，也就是说，tuple呈现出一个异质元素列(heterogeneous list of elements)
 * ! 其中每个类型都可以被指定，或用于编译期推到
 * @param template <typename... Type>
 * 
 * ? 而tuple的接口很直观，通过构造或者make_tuple()都可以创建一个tuple
 * ? 而通过get<>() function template, 可以访问tuple的元素
*/

void foo() {
    // ? 创建一个四元素的tuple, 且被默认初始化
    std::tuple<std::string, int, int, std::complex<double>> t;

    // ? 创建一个隐式转化初始化的tuple
    std::tuple<int, float, std::string> t1(41, 6.3, "nico");

    // ? “迭代”每个元素
    std::cout << std::get<0>(t1) << " ";
    std::cout << std::get<1>(t1) << " ";
    std::cout << std::get<2>(t1) << " ";
    std::cout << "\n";

    auto t2 = std::make_tuple(22, 44, "nico");
    std::cout << std::get<1>(t2) << std::endl;
}

/**
 * ! 注意，tuple的元素类型可以是reference的，不需要像pair一样使用std::ref()才能引用
 * ! tuple不是寻常的容器，因此不允许迭代元素，但是tuple提供了std::get<>()来处理其元素，因此你必须在编译期就知道其元素索引值
*/

void foo1() {
    std::string s;
    std::tuple<std::string&> t(s);

    std::get<0>(t) = "hello";
    std::cout << s << std::endl;   
}

void foo2() {
    // ? 当你想要改动tuple中的既有值
    std::string s;
    auto x = std::make_tuple(s);
    std::get<0>(x) = "my value";

    auto y = std::make_tuple(std::ref(x));
    std::get<0>(y) = "my value";

    // ? 运用reference 搭配 make_tuple()，就可以提取tuple的元素值，且设置给他们
    std::tuple<int, float, std::string> t(77, 1.1, "more light");
    int i;
    float f;
    std::string s1;

    std::make_tuple(std::ref(i), std::ref(f), std::ref(s1)) = t;
    std::cout << i << " " << f << " " << s1 << std::endl;   

    // ! 如果想最方便的使用上面的功能，选择tie()会更加便利，可以在内部建立一个reference 的tuple
    std::tie(i, f, s1) = t;
    std::cout << i << " " << f << " " << s1 << std::endl;   

    // ? 当然的，在使用tie的时候，我们可以忽略一些元素，std::ignore能够使我们局部的提取tuple中的值
    std::tie(i, std::ignore, s1) = t;
}

/**
 * ! 在tuple中，接受不定参的构造函数被设置为explicit，因此不允许在构造的时候进行隐式转换，必须明确知道其类型
*/

void foo3() {
    // ! 因此，我们不可以像以下这样 “期望获取一个tuple” -> C++11 但是实际测试是允许的
    std::vector<std::tuple<int, float>> v {
        {1, 1.0}, {2, 2.0}
    };
    std::cout << std::get<0>(v[0]) << std::endl;

    // ! C++11中，必须明确指出tuple
    std::vector<std::tuple<int, float>> v1 {
        std::make_tuple(1, 1.0), 
        std::make_tuple(2, 2.0)
    };
    std::cout << std::get<1>(v1[0]) << std::endl;
}

/**
 * ! tuple的辅助函数
 *  ! tuple_size<>::value可以获取tuple的元素个数
 *  ! tuple_element<>::type可以获取对应元素的类型，也就是std::get<>()的类型
 *  ! tuple_cat() 可将多个tuple串接为一个tuple
*/

void foo4() {
    using TupleType = std::tuple<int ,float, std::string>;
    std::cout << "tuple size: " << std::tuple_size<TupleType>::value << std::endl;  

    std::tuple_element<2, TupleType>::type s = "hello world";

    // ! 而tuple_cat可以串接所有形式的tuple，包括pair
    int n = 0;
    auto tt = std::tuple_cat(
        std::make_tuple(42, 7.7, "hello"), std::tie(n), std::make_pair(12, 5)
    );
}

int main() {
    foo();
    foo1();
    foo2();
    foo3();
    return 0;
}