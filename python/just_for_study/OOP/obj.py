# ! 私有属性和私有方法
# ! 在python中类对于成员没有严格限制访问。
# ? 通过约定，以两个下划线开头的是私有的(private),其他的为公开的(public)
# ? 类内部可以访问私有属性(方法)
# ? 类外部不能直接访问私有属性(方法)
# ? 类外部可以通过用类域指定私有属性来访问

# TODO 类外想要访问私有属性，必须_类名__私有属性访问
class Employee :
    def __init__(self, name, age) :
        self.name = name
        self.__age = age
    
    def __work(self) :
        print("好好工作")

e = Employee("lily", 18)
print(e.name)
print(e._Employee__age)
e._Employee__work()

# ! @property装饰器，可以将一个方法的调用方式变成属性调用
# ! 常用于修饰get和set方法，类似于const，权限修改为只读
class Employer :
    @property
    def salary(self) :
        pass

emp1 = Employer()
print(emp1.salary)

class Employee :
    def __init__(self, name = "", salary = 1000) :
        self.__name = name
        self.__salary = salary

    @property
    def salary(self) :
        return self.__salary

    # ! 此处的salary就是刚刚用property修饰的方法
    # ! 相当于salary的设置方案
    @salary.setter
    def salary(self, salary) :
        if 1000 < salary < 50000 :
            self.__salary = salary
        else :
            print("录入错误")
'''
    def get_salary(self) :
        return self.__salary

    def set_salary(self, salary) :
        if 1000 < salary < 50000 :
            self.__salary = salary
        else :
            print("录入错误")
'''

emp1 = Employee("lily")
emp1.salary = 5000
print(emp1.salary)
        





