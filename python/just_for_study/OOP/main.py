# ! 类和对象
class Stu :
    '''在C++中，this(self)是内置隐藏的，而python是显式的，并且必须通过__init__方法构造，并且第一个参数必须是self'''
    def __init__(self, name, score) :
        self.name = name
        self.score = score
    
    def show_score(self) :
        print("{0}的分数是：{1}".format(self.name, self.score))
    
# ? 在python中，使用类名直接调用构造函数，且python只有一个构造函数
s1 = Stu("lily", 60)
s1.show_score()
# ! 实际结构
Stu.show_score(s1)

# ! 构造函数__init__()只能由这个方法去构造，且通过类名来调用
# ! 在python中，没有构造函数也能够使用
# ! 创建堆区__new__()
# ! 在python中，对象可以自己创建一个成员变量(自身私有)
s1.age = 18
print(s1, s1.age)

# ! dir()方法，获得所有属性和方法
print(dir(s1))
# ! obj.__dict__获得自定义的属性和方法，并且以字典的形式打印
print(s1.__dict__)
# ? pass语句，空语句

# ! isinstance()判断一个对象是不是一个类的成员
print(isinstance(s1, Stu))

# ! 也可以通过类创建一个类对象
s = Stu
s1 = s("hello", 100)
s1.show_score()

# ! 在python中类属性就等同于C++中的成员变量，但是在类中的方法使用的时候依旧需要使用类名作为域

class A :
    a = 0
    b = "hello"
    
    def __init__(self) :
        A.a = 1
        A.b = "wow"
        
    def show_the(self) :
        print("{0} -- {1}".format(A.a, A.b))
        
a = A()
a.show_the()

# ! 类方法是从属于类对象的方法，需要有一个标记@classmethod,第一个参数必须是cls
class Student :
    company = "nullptr"
    @classmethod
    def printfCompany(cls) :
        print(cls.company)
    
Student.printfCompany()

# ! 静态方法(与类无关的方法)，需要使用类名作为作用域调用，通过@staticmethod定义
# ? 静态方法无权访问实例和方法，但是可以用类名作为作用域引用
class B :
    @staticmethod
    def add(x, y) :
        print(x + y)
        
B.add(1, 3)

# ! 类方法和静态方法中不能调用实例对象和属性，除非使用域

# ! python的析构函数为__del__，系统会自动提供析构函数
class Person :
    def __del__(self) :
        print("销毁{0}".format(self))
        
p1 = Person()
p2 = Person()
# ! 也可以通过del方法手动删除对象

# ! __call__方法，被称为可调用对象，表示对象能够像函数一样调用
class SalaryAccont :
    def __call__(self, *args, **kwds) :
        print("算工资...")
        return 3000
    
s = SalaryAccont()
s()

# ! python中方法是没有重载的，定义的同名方法，只有最后一个有效
# ! python是动态语言。可以动态的添加方法
class Per :
    def work(self) :
        print("努力上班!")
        
def play_game(s) :
    print("{0}在玩游戏".format(s))

Per.play = play_game
p = Per()
p.work()
p.play()


