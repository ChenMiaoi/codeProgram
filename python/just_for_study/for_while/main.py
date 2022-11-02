
# ! while循环


num = 0
while num <= 10 :
    print(num)
    num += 1

a = [1,9,4,5,6,7,2,3,8,0,10]
count = len(a)
i = 0
j = 0
while i < count - 1 :
    while j < count - i - 1 :
        if a[j] > a[j + 1] :
            temp = a[j]
            a[j] = a[j + 1]
            a[j + 1] = temp 
        j += 1
    i += 1
print(a)

sum = 0
num = 0
while num <= 100 :
    sum += num
    num += 1
print(sum)


# ! for循环
# ? 可迭代对象：
'''
    1. 序列。 包括：字符串、列表、元组
    2. 字典
    3. 迭代器对象 (iterator)
    4. 生成器对象 (generator)
'''
for x in (3,4,5) :
    print(x * 3)
    
for x in [3,4,5] :
    print(x * 10)
    
for x in "abcdefg" :
    print(x)

d = {"name":"hehe", "age":18, "job":"stu"}
for x in d :
    print(x)
    
for x in d.keys() :
    print(x)
    
for x in d.values() :
    print(x)
    
for x in d.items() :
    print(x)

for i in range(0, 10) :
    print(i)
    
sum = 0
for i in range(1, 101, 2) :
    sum += i
print(sum)

sum = 0
for i in range(0, 101, 2) :
    sum += i
print(sum)

# ! 循环嵌套
for x in range(5) :
    for y in range(5) :
        print(x, end = '\t')
    print()


for m in range(1, 10) :
    for n in range(1, m + 1) :
        print("{0} * {1} = {2}".format(m, n, m * n), end = '\t')
    print()

# ! break语句
for x in range(10) :
    if x == 5 :
        break
    print(x)

# ! continue语句
for x in range(10) :
    if x == 5 :
        continue
    print(x)

# ! 在python中，循环也有else，如果没有break，那么结束循环后会进行else


# ! 循环的优化
# ! 尽量减少循环内部不必要的计算
# ! 嵌套循环中，尽量减少内层循环的计算
# ! 局部变量查询较快
import time

start = time.time()
for i in range(1000) :
    result = []
    for m in range(10000) :
        result.append(i * 1000 + m * 100)
end = time.time()
print("{0}".format(end - start))


# ! zip并行迭代
names = {"hehe", "haha", "lili"}
ages = {18, 20, 17}

for name,age in zip(names, ages) :
    print("{0} -- {1}".format(name, age))

'''  
def febo(n) :
    if n > 2 :
        return febo(n - 2) + febo(n - 1)
    elif n == 1 or n == 2:
        return 1
    else :
        return 

start = time.time()

febo(50)

end = time.time()
print("febo : {0}".format(end - start))
'''

# ! 推导式
# ! 列表推导式
a = [x for x in range(1, 5)]
print(a)

a = [x * 2 for x in range(1, 5)]
print(a)

# ! 字典推导式
# TODO {key : value for condition in dict}
b = "hello world"
count = {c : b.count(c) for c in b}
print(count)

# ! 集合推导式
b = {x for x in range(100) if x % 9 == 0}
print(b)

# ! 生成器推导式(生成元组)
# ! 注意，生成器只能使用一次
gt = (x for x in range(1, 100) if x % 9 == 0)
for x in gt :
    print(x, end = ' ')
print()

for x in gt :
    print(x, end = " ")
print()

import turtle
t = turtle.Pen()

t.circle(100)
turtle.done()
