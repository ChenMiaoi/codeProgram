from socket import socket


num = input("输入一个数字: ")
# !这里的int需要转型，因为这里的num是字符串 

'''
if int(num) < 10 :
    print(num)

if 3 :
    print("ok")
'''

# !空列表不会被认为是False
a = []
if a :
    print("空列表, False")

s = "False"
if s :
    print("非空字符串, True")

c = True
if c :
    print("True");

# !在python中支持连续判断
d = 5
if 0 < d < 10 :
    print(d)

# ! 在python中条件表达式中不能出现赋值操作符，避免了将 "==" 写成 "="的操作

# ! 双分支if
'''
s = input("请输入一个数字: ")

if int(s) < 10 :
    print("s是小于10的数字")
else :
    print("is not")
'''

# !python的三元表达式： condition1 if condition2 else condition3

num = 10
num if int(num) else "数字太大"

# !多分支选择结构

'''
    if condition1
        ...
    elif condition2
        ...
    ...
    [
    else
        ...
    ]
'''

# ! 确定一个学生成绩的好坏
score = 79
grade = ""
if score < 60 :
    grade = "fail"
elif score < 80 :
    grade = "C"
elif score < 90 :
    grade = "B"
elif score <= 100 :
    grade = "A"
else :
    print("error")

print("score is {0}, garde is {1}".format(score, grade))

# ! 选择结构的嵌套 -- 注意缩进量
'''
    if condition1 :
        ...
        if condition2 :
            ...
        else :
            ...
    else :
        ...
'''

