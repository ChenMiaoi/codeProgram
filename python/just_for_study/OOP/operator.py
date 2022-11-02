
# TODO 运算符的重载和特殊方法

# ! a + b 本质上是调用的a.__add__(b)方法
# ! 在py中每一个运算符都重载了一个对应的方法

# ! 操作符
'''
    __add__ __sub__ __mul__     加  减  乘
    __truediv__ __mod__ __floordiv__    浮点除  取模    整除
    __it__  __le__  __eq__      小于    小于等于    等于
    __gt__  __ge__  __ne__      大于    大于等于    不等于
    __or__  __xor__ __and__     或      异或    与
    __lshift__  __rshift__      左移    右移
    __pow__         指数运算
'''

# ! 特殊方法
'''
    __init__                构造
    __del__                 析构
    __repr__    __str__     打印    转换
    __call__                函数调用
    __getattr__             点号运算
    __setattr__             属性赋值
    __getitem__             索引运算    a[key]
    __setitem__             索引赋值    a[key] = val
    __len__                 长度        len()
'''

from copy import copy


class Person :
    def __init__(self, age) :
        self.age = age
        
    def __add__(self, p) :
        if isinstance(p, Person) :
            return self.age + p.age
        else :
            return 
        
p1 = Person(18)
p2 = Person(20)
x = p1 + p2
print(x)

# ! 特殊属性
'''
    obj.__dict__            对象的属性字典
    obj.__class__           对象所属的类
    obj.__bases__           类的基类元组(多继承)
    obj.__base__            类的基类
    obj.__mro__             类的层次结构
    obj__subclasses__()     子类列表
'''

class A :
    pass

class B :
    pass

class C(A, B) :
    pass

c = C()
print(c.__dict__)
print(c.__class__)
print(C.__bases__)
print(A.__subclasses__())

# ! 对象的浅拷贝和深拷贝
# ? python中的拷贝一般是浅拷贝，对象包含的对象会引用同一个子对象
# ? 深拷贝产生的子对象不是指向同一对象

import copy
class MobilePhone : 
    def __init__(self, cpu, screen) :
        self.cpu = cpu
        self.screen = screen
class CPU :
    def calculate(self) :
        print("cpu : ", self)
class Screen :
    def show(self) :
        print("screen : ", self)

# TODO 测试浅拷贝
c1 = CPU()
s1 = Screen()
m1 = MobilePhone(c1, s1)
m2 = copy.copy(m1)

print("测试浅拷贝")
print(m1, m1.cpu, m1.screen)
print(m2, m2.cpu, m2.screen)

# TODO 测试深拷贝
m3 = copy.deepcopy(m1)
print("测试深拷贝")
print(m1, m1.cpu, m1.screen)
print(m3, m3.cpu, m3.screen)

# ! 浅拷贝 -- 对象地址不一样，但是内部属性和方法指向同一块空间
# ! 深拷贝 -- 对象地址不一样，同时内部属性和方法指向不同的空间

# ! 组合
'''
    is  - a关系：类似于继承，他是属于他的
        dog is animal
    has - a关系：类似于拥有，他里面包含他
        MobilePhone has a CPU
'''

class A :
    def say_word(self) :
        print("hhh")

class B :
    def __init__(self, a) :
        self.a = a

a = A()
b = B(a)
b.a.say_word()