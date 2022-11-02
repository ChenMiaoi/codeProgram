# ! func
from cgi import test
from re import A
from socket import inet_ntoa


def test1() :
    print("test1")

test1()
print(id(test1))
print(type(test1))

# ! 形参和实参
def Max(x, y) :
    if x > y :
        return x
    else :
        return y
    
max = Max(1, 2)
print(max)

# ! 函数文档注释，直接在函数内部的第一行写
def Min(x, y) :
    '''用于比较两个数的大小，并且返回在于最小值'''
    if (x > y) :
        return y
    else :
        return x

# ? 函数的文档注释是可以通过内置函数help去查看的
help(Min.__doc__)

# ! 在python中，函数如果没有返回值，自动返回None

def my_avg(x, y) :
    return (x + y) / 2

c = my_avg(1, 2)
print(c)

# ! 在python中提供了一种在函数内部定义全局变量的关键字 global
a = 10
def test2() :
    global a 
    a = 20

test2()
print(a)

# ! 在python中传递的都是引用传递
# ! 传递可变对象的时候，地址不会改变
b = [10, 20]
def f2(m) :
    print("m : ", id(m))
    m.append(30)
    
f2(b)
print("b : ", id(b))
print(b)

# ! 传递不可变对象的时候，地址传递会改变
a = 100
def f3(n) :
    print("n : ", id(n))
    n = n + 2
    print("n : ", id(n))

f3(a)
print("a : ", id(a))

# ! 深拷贝和浅拷贝
# TODO 浅拷贝会将地址一起拷贝(C++) -- 会影响源对象
# TODO 深拷贝不会将地址一起拷贝(C++) -- 不会影响源对象
# ! 在python里面浅拷贝不会拷贝地址，但是会影响与源对象相同的位置
# ! 在python里面深拷贝不会拷贝地址，但是不会影响源对象
import copy
def testCopy() :
    '''测试浅拷贝'''
    a = [10, 20, [5, 6]]
    b = copy.copy(a)
    print("a : ", id(a))
    print("a : ", a)
    print("b : ", id(b))
    print("b : ", b)
    b[2].append(1)
    print("a : ", a)
    print("b : ", b)
    print()
    
testCopy()

def testDeepCopy() :
    a = [10, 20, [5, 6]]
    b = copy.deepcopy(a)
    print("a : ", id(a))
    print("a : ", a)
    print("b : ", id(b))
    print("b : ", b)
    b[2].append(1)
    b.append(2)
    print("a : ", a)
    print("b : ", b)

testDeepCopy()

# ! 传递不可变对象发生可变时，是浅拷贝
a = (10, 20, [5 ,6])
print("a : ", id(a))
def f6(m) :
    print("m : ", id(m))
    m[2][0] = 888
    print(m)
    print("m : ", id(m))
    
f6(a)
print("a : ", id(a))

# ! 可变参数
# ? 1. *param(一个星号)，表示将多余的数据放在元组里
# ? 2. **param(两个星号)，表示将多余的数据放在字典里
def n1(a, b, *c) :
    print(a, b, c)
    
n1(8, 9, 10, 11, 12)

def n2(a, b, **c) :
    print(a, b, c)
    
n2(8, 9, name = "lily", age = 18)

# ! 强制命名参数
# ? 在可变参数后面的参数，必须在传参的时候强制命名
def n3(*a, b, c) :
    print(a, b, c)

n3(1, 2, 3, b = 4, c = 5)

# ! lambda表达式
# TODO 用来定义一个简单函数方法，计算的结果就是返回值
# TODO lambda arg1, arg2, arg3 ... : <condition>
f = lambda a, b, c : a + b + c
print(f)
print(f(1,2,3))

g = [lambda a : a * 2, lambda b : b * 3, lambda c : c * 4]
print(g[0](6), g[1](7), g[2](8))

# ! eval函数
# TODO 将str转化成一段计算函数并且返回计算结果
str = "print('abcde')"
eval(str)

# TODO 递归
def func(n) :
    if n == 1 :
        return 1
    elif n > 1 :
        return n * func(n - 1)
    
print(func(5))

# ! 嵌套函数(内部函数)
def f1() :
    print("f1 running...")
    def f2() :
        print("f2 running...")
    f2()
    
# ! 对于定义在内部的函数，只能在内部使用无法在外部调用
f1()

def ChineseName(name, familyName) :
    print("{0}   {1}".format(familyName, name))
    
def EngLishName(name, familyName) :
    print("{0}   {1}".format(name, familyName))
    
def Name(isChinese, name, familyName) : 
    def inner_print(a, b) :
        print("{0}    {1}".format(a, b))
    
    if isChinese :
        inner_print(familyName, name)
    else :
        inner_print(name, familyName)
        
# ! 在之前我们提到，在函数内部可以使用global来定义一个全局变量(类似于static扩展作用于的操作)
# TODO 现在有一个来声明外层的局部变量 -- nonlocal
def f1() :
    b = 10
    def f2() :
        nonlocal b #!声明外部函数的局部变量，就可以在内部使用修改
        print("f1() b :", b)
        b = 20

# ! LEGB规则，python在查找名称的时候，是按照这个规则依次查找的
# TODO Local -- 函数或者类的方法内部
# TODO Enclosed -- 嵌套函数
# TODO Global -- 模块中的全局变量
# TODO Built in -- python为自己保留的特殊名称
# ! 如果没有找到就会产生NameError
def outer() :
    str = "outer"
    def inner() :
        str = "inner"
        print(str)
        pass
    inner()
    
outer()