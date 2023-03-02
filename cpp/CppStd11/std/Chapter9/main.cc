#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

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

int main() {
    foo();
    foo1();
    foo2();
    foo3();
    return 0;
}
