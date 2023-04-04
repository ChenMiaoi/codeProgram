#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>
#include <set>

/**
 * @brief 迭代器种类
 * ! OutPut迭代器，OutPut迭代器允许一步一步前行并搭配write动作
 * ! InPut迭代器，InPut迭代器只能一次一个以前行的方向读取元素，按此顺序一个个返回元素值
 * ! Forward迭代器，是一种input迭代器且在前进读取时提供额外保护
 * ! Bidirectional(双向)迭代器，在forward的基础上增加了回头迭代的能力，也就是说，支持递减操作符
 * ! Random-Access(随机访问)迭代器，在bidirectional迭代器的基础上增加了随机访问能力，因此必须提供iterator算数运算，以及关系运算符
 * */

/**
 * @brief 迭代器相关辅助函数
 * ! advance(InputIterator& pos, Dist n)，可将迭代器的位置增加，增加幅度由实参决定，也就是说令迭代器一次前进(或后退)多个元素
 *  @param pos 令pos前进或后退n个元素
 *  @brief advance并不检查迭代器是否超过序列的end()，也就是说，调用advance可能导致未定义行为的发生
 * */

void foo() {
    std::list<int> coll;
    for (int i = 1; i < 10; i++)
        coll.push_back(i);
    std::list<int>::iterator pos = coll.begin();

    std::cout << *pos << std::endl;
    std::advance(pos, 3);
    std::cout << *pos << std::endl;
    std::advance(pos, -1);
    std::cout << *pos << std::endl;
}

/**
 * @brief next() and prev()
 * ! 自C++11起，提供了两个新增的辅助函数，允许你前进或后退移动迭代器
 * ! ForwardIterator next (ForwardIterator pos)
 * ! ForwardIterator next (ForwardIterator pos, Dist n)
 * ? 其类型是std::iterator_traits<ForwardIterator>::difference_type
 * ? 其内部会对临时对象调用advance(pos, n)
 *
 * ! BidirectionalIterator next (BidirectionalIterator pos)
 * ! BidirectionalIterator next (BidirectionalIterator pos, Dist n)
 * ? 其类型是std::iterator_traits<BidirectionalIterator>::difference_type
 * ? 其内部会对临时对象调用advance(pos, -n)
 * */

void foo1() {
    std::list<int> coll;
    for (int i = 1; i < 10; i++)
        coll.push_back(i);
    std::list<int>::iterator pos = coll.begin();

    while (pos != coll.end() && std::next(pos) != coll.end()) {
        ++pos;
    }
}

/**
 * @brief distance()
 * ! Dist distance(InputIterator pos1, InputIterator pos2)
 * ? 返回两个迭代器pos1和pos2之间的距离
 * ? 如果不是random-access迭代器，则从pos1开始前进必须能够到达pos2，也就是说，pos2必须在其后面或相同位置
 * ? 其类型是std::iterator_traits<InputIterator>::difference_type
 * ! 对于random-access迭代器，此函数是O(1)，而对于其他迭代器，则是线性复杂度，因此一般用于random-access而非其他
 * */

void foo2() {
    std::list<int> coll;
    for (int i = -3; i <= 9; i++)
        coll.push_back(i);
    std::list<int>::iterator pos;
    pos = std::find(coll.begin(), coll.end(), 5);
    if (pos != coll.end()) {
        std::cout << "difference between beginning and 5: " << std::distance(coll.begin(), pos) << std::endl;
    } else{
        std::cout << "5 not found" << std::endl;
    }
}

/**
 * @brief iter_swap()
 * ! void iter_swap(ForwardIterator1 pos1, ForwardIterator2 pos2)
 * ? 交换迭代器pos1和pos2所指向的值
 * ! 迭代器的类型不必相同，但是所指向的值必须可以互相赋值
 * */

void foo3() {
    std::list<int> coll;
    for (int i = 1; i <= 9; i++)
        coll.push_back(i);
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::iter_swap(coll.begin(), std::next(coll.begin()));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
    std::iter_swap(coll.begin(), std::prev(coll.end()));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
}

/**
 * ! 可以让正常迭代器转化为反向迭代器，也可以通过base()将反向迭代器转化为正常
 * */

void foo4() {
    std::list<int> coll { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::list<int>::const_iterator pos = std::find(coll.begin(), coll.end(), 5);
    std::cout << "pos: " << *pos << std::endl;
    std::list<int>::const_reverse_iterator rpos(pos);
    std::cout << "rpos: " << *rpos << std::endl;
    std::list<int>::const_iterator rrpos = rpos.base();
    std::cout << "rrpos: " << *rrpos << std::endl;
}

/**
 * ! Back Insert借由成员push_back()，back insert生成时，其初始化必须明确知道所属容器
 * ? 可以通过std::back_insert_iterator<> 来获取迭代器，然后进行插入
 * ? 另外一种简单的方式为：通过std::back_insert()来插入
 * */

void foo5() {
    std::vector<int> coll;
    std::back_insert_iterator<std::vector<int>> iter (coll);
    *iter++ = 1;
    *iter++ = 2;
    *iter++ = 3;
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::back_inserter(coll) = 44;
    std::back_inserter(coll) = 55;
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
    coll.reserve(2 * coll.size());
    std::copy(coll.begin(), coll.end(), std::back_inserter(coll));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
}

/**
 * ! Front Insert借由成员push_front()，front insert生成时，其初始化必须明确知道所属容器
 * ? 可以通过std::front_insert_iterator<> 来获取迭代器，然后进行插入
 * ? 另外一种简单的方式为：通过std::front_insert()来插入
 * */

void foo6() {
    std::list<int> coll;
    std::front_insert_iterator<std::list<int>> iter (coll);
    *iter++ = 1;
    *iter++ = 2;
    *iter++ = 3;
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::front_inserter(coll) = 44;
    std::front_inserter(coll) = 55;
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::copy(coll.begin(), coll.end(), std::front_inserter(coll));
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";
}

/**
 * ! General Inserter，根据两个实参完成初始化：容器和待安插位置，迭代器内部以"待安插位置"为实参调用成员函数insert)_
 * ! 而inserter()是便捷的接口，general inserter对所有容器均适用(除array和forward list)
 * ! 安插完毕后，相当于为 pos = container.insert(pos, value); ++pos; 为了防止迭代器失效
 * */

void foo7() {
    std::set<int> coll;
    std::insert_iterator<std::set<int>> iter (coll, coll.begin());
    *iter++ = 1;
    *iter++ = 2;
    *iter++ = 3;

    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::inserter(coll, coll.end()) = 44;
    std::inserter(coll, coll.end()) = 55;
    for (const auto& i : coll)
        std::cout << i << " ";
    std::cout << "\n";

    std::list<int> coll2;
    std::copy(coll.begin(), coll.end(), std::inserter(coll2, coll2.begin()));
    for (const auto& i : coll2)
        std::cout << i << " ";
    std::cout << "\n";

    std::copy(coll.begin(), coll.end(), std::inserter(coll2, std::next(coll2.begin())));
    for (const auto& i : coll2)
        std::cout << i << " ";
    std::cout << "\n";
}

/**
 * ！ Ostream iterator可以将"被赋值"写入output stream中，因此，算法就可以直接写入stream，其与上述唯一的区别就是将赋值动作自动转化为output动作
 * */

void foo8() {
    std::ostream_iterator<int> intWriter(std::cout, " "); // ! 后面的参数为分隔符
    // ! 需要注意的是，分隔符是const char*类型，因此传入string需要string::c_str()
    *intWriter++ = 42;
    *intWriter++ = 77;
    *intWriter++ = -5;

    std::vector<int> coll { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;

    std::copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " < "));
    std::cout << std::endl;
}

/**
 * ! istream iterator是ostream迭代器的搭档，用来从input stream中读取元素。
 * ! 建立istream迭代器时，必须提供一个input stream作为实参，因为读取元素可能失败(读取到尾部，或读取错误，因此，可以使用一个
 * ! 所谓的end-of-stream迭代器(也就是istream iterator = default构造)，只要有任何一次读取失败，所有的istream迭代器都会变为end-of-stream
 * */

void foo9() {
    std::istream_iterator<int> intReader (std::cin);
    std::istream_iterator<int> intReaderEOF;

    while (intReader != intReaderEOF) {
        std::cout << "once: " << *intReader << std::endl;
        std::cout << "once again: " << *intReader << std::endl;
        ++intReader;
    }
}

void foo10() {
    std::istream_iterator<std::string> cinPos(std::cin);
    std::ostream_iterator<std::string> coutPos(std::cout, " ");

    while (cinPos != std::istream_iterator<std::string>()) {
        std::advance(cinPos, 2); // ! 使得cinPos强制前进两个单位，即忽略了前两个输入

        if (cinPos != std::istream_iterator<std::string>()) { // ! advance不进行检查，防止读取错误
            *coutPos++ = *cinPos++;
        }
    }
    std::cout << std::endl;
}

int main() {
    foo();
    foo1();
    foo2();
    foo3();
    foo4();
    foo5();
    foo6();
    foo7();
    foo8();
    // foo9();
    foo10();
    return 0;
}
