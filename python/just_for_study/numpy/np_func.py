import numpy as np
# TODO numpy的算术函数
# ! 对于两个对象，都是ndarray且形状(行列)相同，则能够进行运算
'''
    np.add()
    np.subtract()
    np.multiply()
    np.divide()
'''

a = np.arange(9).reshape(3, 3)
b = np.array([10, 10, 10])
print(np.add(a, b))
print(a + b)
print(np.subtract(a, b))
print(a - b)

# ! out参数的使用
y = np.empty((3, 3))
np.multiply(a, 10, out = y)
print(y)

# TODO 三角函数
'''
    np.sin()
    np.cos()
    np.tan()
'''

a = np.arange(5)
print(np.sin(a))

# TODO 
a = np.array([1.0, 4.55, 123, 0.567, 25.332])
# ! np.around 四舍五入 
print(np.around(a))
# ! np.ceil 向上取整
print(np.ceil(a))
# ! np.floor 向下取整
print(np.floor(a))

# TODO 聚合(统计)函数
'''
    np.sum()        --求和
    np.prod()       --所有元素相乘
    np.mean()       --平均值
    np.std()        --标准差
    np.var()        --方差
    np.median()     --中数
    np.power()      --幂运算
    np.sqrt()       --开方
    np.min()        --最小值
    np.max()        --最大值
    np.argmin()     --最小值的下标
    np.argmax()     --最大值的下标
    np.inf()        --无穷大
    np.exp()        --以e为底的指数
    np.log()        --对数
'''
a = np.arange(12).reshape(3, 4)
print(a)
print(np.power(a, 2))

# TODO np.median() 对于二维及其以上的矩阵需要指定axis轴
a = np.arange(1, 13).reshape(3, 4)
print(a)
print(np.median(a, axis = 0))
print(np.median(a, axis = 1))
