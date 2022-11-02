
# ! Exception例外，在编程中称之为异常
'''
    try...except是最常见的异常处理结构
    try:
        被监控的可能引发错误的代码
    except BaseException[as e]:
        异常处理
    
    如果try中异常了，从异常开始的以后的代码就会被跳过直接执行异常处理
'''

import imp
from tokenize import Name


try :
    print("step1")
    a = 3 / 0
    print("step2")
except :
    print("step3")
print("step4")

'''
# TODO 循环输入数字，不是数字就处理异常
while True :
    try :
        x = int(input("请输入一个数字:> "))
        print("输入的数字: ", x)
        if x == 88 :
            print("退出程序")
            break
    except :
        print("必须输入一个数字VALUE ERROR！")
'''

# TODO 多个except结构 ： 按照先子类后基类 -- 最好在最后面使用BaseException
try :
    a = input()
    b = input()
    c = float(a) / float(b)
except ZeroDivisionError :
    print("不能除以0")
except ValueError :
    print("不能将字符串转化为为数字")
except NameError :
    print("变量不存在")
except BaseException as e:
    print(e)
else :
    print(c)
finally :
    print("我是finally，无论如何都会实现")
    
# ! else结构，如果没有异常就执行else，有异常就执行except

# ! finally结构，finally结构内的代码无论如何都会被执行，通常用来释放try中申请的资源
# ! 尽量不要再抛异常内使用return语句

# ! 常见错误汇总
'''
    # ? SyntaxError : 语法错误
    # ? NameError : 尝试访问一个没有声明的变量
    # ? ZeroDivisionError : 除数为0
    # ? ValueError : 数值错误
    # ? TypeError : 类型错误
    # ? AttributeError : 访问对象的不存在属性
    # ? IndexError : 索引越界异常
    # ? KeyError : 字典的关键字不存在
    # ? ArithmeticError : 所有数值计算错误的基类
    # ? AssertionError : 断言语句失败
    # ? BaseException : 所有异常的基类
    # ? DeprecationWarning : 关于被弃用的特征的警告
    # ? EnvironmentError : 操作系统错误的基类
    # ? EOFError : 没有内建输入,到达EOF标记
    # ? Exception : 常规错误的基类
    # ? FloatingPoiontError : 浮点计算错误
    # ? FutureWaring : 关于构造将来语义会有改变的警告
    # ? GeneratorExit : 生成器发生异常来通知退出
    # ? ImportError : 导入模块/对象失败
    ...
'''
# ! 上下文管理器 -- with
# TODO with context_expr[as var] :

# ! trackback模块
import traceback
try :
    print("step1")
    num = 1 / 0
except :
    traceback.print_exc()

# TODO 将异常信息输出到指定文件
try :
    print("step1")
except :
    with open(...) as f :
        traceback.print_exc(file = f)
        
# ! 自定义异常类 -- raise
class AgeError(Exception) :
    def __init__(self, errorInfo) :
        self.errorInfo = errorInfo
    def __str__(self) :
        return "AGE ERROR!"

if __name__ == "__main__" :
    age = int(input("请输入一个年龄: "))
    if age < 1 or age > 150 :
        raise AgeError(age)
    else :
        print("正常的年龄: ", age)
        

