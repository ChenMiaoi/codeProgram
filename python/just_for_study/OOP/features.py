
# ! 三大特性 -- 封装继承多态

# TODO 继承
# ? python的继承大致和C++，也支持多继承，子类可以直接重写基类
# ! 定义子类时，(逻辑上，但是语法上没有严格限制)必须在构造函数中调用基类的构造函数
# ! 和C++类似的，私有属性可以继承给子类，但是对于子类来说，基类的私有对象是不可见的
# ! 但是在python中，私有属性不是绝对私有的，可以通过指明类域来引用
from regex import P


class Person :
    def __init__(self, name = "lily", age = 18) :
        self.name = name
        self.age = age
    
    def show_person(self) :
        print("{0} -- {1}".format(self.name, self.age))
        
class Student(Person) :
    def __init__(self, name="lily", age=18, score = 0):
        super().__init__(name, age) # ! 此处的super()就是基类
        self.score = score
        
    def show_person(self):
        return super().show_person()

s = Student()
s.show_person()
print(s.score)

# TODO 重写方法
# ! 子类可以重新定义基类的方法，但是会覆盖掉从基类继承的方法

# TODO 通过mro()或者属性__mro__()可以查看类的继承关系
print(Student.mro())

# ! object根类，是所有类的基类，所有的类都有该类的属性和方法
obj = object()
print(dir(obj))
print(dir(s))

# ! 重写__str__()方法，用于返回一个对于对象的描述
class Person :
    def __init__(self, name = "lily", age = 18) :
        self.name = name
        self.age = age
    
    def show_person(self) :
        print("{0} -- {1}".format(self.name, self.age))
        
    def __str__(self) :
        return "Name is : {0}".format(self.name)
    
p = Person()
print(p)

# ! 和C++类似，支持多继承，但是尽量避免多继承

# TODO MRO()函数 ： 如果基类中有相同名字的方法，且子类没有指定
# TODO 基类时，解释器按照"从左向右"顺序搜索，MRO方法解析顺序
# ! 当多继承的时候，对于python的子类而言，是没有解决方案的
# ! 只能通过MRO来确定具体调用的方法，而C++通过virtual解决

# ! super()获取基类的定义 -- 注意！ 不是基类对象
class A :
    def say(self) :
        print("A : ", self)

class B(A) :
    def say(self) :
        super().say()
        print("B : ", self)
        
B().say()

# TODO 多态 -- python的多态，不是严格意义上的多态，仅仅类似于重写基类函数
# ! 1. 多态是方法的多态，属性没有多态
# ! 2. 多态的存在有两个必要条件 ： 继承、方法重写
class Animal :
    def shout(self) :
        print("Animal shout")

class Dog(Animal) :
    def shout(self):
        print("Dog shout")

class Cat(Animal) :
    def shout(self):
        print("Cat shout")

def shout(m) :
    if isinstance(m, Animal) :
        m.shout()
    else :
        Animal.shout()
        
d = Dog()
c = Cat()
shout(d)
shout(c)