# numpy的底层是C，因此运行速度比较快
from queue import PriorityQueue
from re import A
from cupshelpers import Printer
import numpy as np
import math

from regex import B

# TODO 创建一个数组
a = np.arange(10)
print(a)
print(type(a))

# ! 对ndarray对象进行向量处理
print(np.sqrt(a))

# ! 对列表中的元素开平方
b = [3, 4, 9]
result = []
for i in b :
    result.append(math.sqrt(i))
print(result)
    
# TODO 使用array创建数组
# ! dtype = typename, ndmin = n, 指定类型和纬度
a = np.array([1,2,3,4])
print(a)
print(type(a))

b = np.array([[1,2,3],[4,5,6]])
print(b)
print(type(b))

# TODO 使用arange(start, end, step, dtype)
a = np.arange(1, 11)
print(a)
print(type(a))

# TODO 随机数创建numpy.random.random(size=(row, col...)) 且从[0.0, 1.0)
a = np.random.random(size = 5)
b = np.random.random(size = (2,3))
c = np.random.random(size = (2,3,4)) # 两个三行四列
print(a)
print(b)
print(c)

# TODO 随机整数numpy.random.randint(low, high, size, dtype)最小，最大，个数
a = np.random.randint(0,5,3)
print(a)
print(type(a))

b = np.random.randint(5, 11, size = (3, 4))
print(b)

c = np.random.randint(2, 6, size = (2, 3, 4))
print(c)
print(c.dtype)

# TODO 创建一个(期望为0, 方差为1)正态分布np.random.randn(d0, d1,...,dn) d代表维度
a = np.random.randn(4)
print(a)

b = np.random.randn(4, 2)
print(b)

# TODO 创建一个指定的正态分布np.random.normal(loc, scale, size), loc期望，scale方差
a = np.random.normal(3, 4, size = (2, 3))
print(a)

'''
    ndarray.ndim        秩， 轴的数量或者维度的数量
    ndarray.shape       矩阵，n行m列
    ndarray.size        矩阵元素的总个数
    ndarray.dtype       对象的元素类型
    ndarray.itemsize    每个元素的大小，以字节为单位
    ndarray.flags       对象的内存信息
    ndarray.real        元素的实部
    ndarray.imag        元素的虚部
    ndarray.data        包含矩阵的缓冲区，但是一般不用这个属性
'''

# TODO 使用np.zeros(shape, dtype, order) -- 但是全部元素为0
a = np.zeros((2,3), dtype = int)
print(a)

# TODO 使用np.ones(shape, dtype, order) -- 但是全部元素为1
a = np.ones((2,3), dtype = int)
print(a)
print(type(a))

# TODO 使用np.empty(shape, dtype, order) -- 不会初始化，直接开辟指定形状
a = np.empty((2,3), dtype = int)
print(a) 

# TODO 使用np.linspace(start, num, endpoint, retstep, dtype)
'''
    start       序列的起始值
    stop        序列的终止值
    num         生成元素个数
    endpoint    如果为True，就包含终止值，默认是True
    retstep     如果为True就会显示间距，默认是True
'''
a = np.linspace(1, 10, 10)
print(a)

# TODO 使用np.logspace(start, stop, num, endpoint, base, dtype)
# ! base就是对数log的底数
a = np.logspace(1, 10, 10, base = 2)
print(a)

# TODO 矩阵的索引与切片
a = np.arange(10)
print(a)

# TODO 索引
print("索引0处的位置: ", a[0])
print("索引5处的位置: ", a[5])

# ! python能够支持负下标访问(逆序)
print("索引-1处的元素: ", a[-1])

# TODO 切片操作 [start: stop: step] -- [start, stop)
print(a[3:])

# ! 切片操作也支持负索引

x = np.arange(1, 13)
print(x)
a = x.reshape(4, 3)
print(a)
print(a[2])
print(a[2][2])

# TODO 复制矩阵
a = np.arange(1, 13).reshape(3, 4)
print(a)
sub_a = a[ : 2, : 2]
print(sub_a)
sub_a[0][0] = 100
print(sub_a)
print(a)
# ! 通过切片得到的矩阵，运用的浅拷贝，如果对该矩阵操作会影响源数组
# TODO 使用np.copy()方法实现深拷贝
sub_aa = np.copy(a[ : 2, : 2])
sub_aa[0, 0] = 200
print(sub_aa)
print(a)

# TODO 改变矩阵维度
# TODO np.reshape(self, shape, order)
a = np.arange(1, 25)
print(a)
b = a.reshape((4, 6))
print(b)

# !规定，reshape中的-1表示将矩阵转为一维矩阵

# ! 通过如下函数将多维转化为一维
# TODO np.ravel()
# TODO np.flatten()

# TODO 矩阵拼接 -- 参数需要用列表或元组传参
# TODO 水平矩阵拼接， np.hstack([obj1, obj2]) -- 行不变(行数必须相等)，列拼接
a = np.arange(1, 5).reshape(2, 2)
print(a)
b = np.arange(5, 9).reshape(2, 2)
print(b)
c = np.hstack([a, b])
print(c)

# TODO 垂直矩阵拼接， np.vstack([obj1, obj2]) -- 列不变(列数必须相等)，行拼接
a = np.arange(1, 5).reshape(2, 2)
print(a)
b = np.arange(5, 9).reshape(2, 2)
print(b)
c = np.vstack((a, b))
print(c)

# TODO 使用np.concatenate((obj1, obj2...), axis = 0)
# ! axis代表了拼接方向，默认是0(垂直方向拼接), 为1(水平方向拼接), 为2(纵深方向拼接)
a = np.arange(1, 5).reshape(2, 2)
print(a)
b = np.arange(5, 9).reshape(2, 2)
print(b)
c = np.concatenate((a, b), axis = 0)
print(c)

a = np.arange(1, 13).reshape(1, 2, 6)
b = np.arange(101, 113).reshape(1, 2, 6)

r1 = np.concatenate((a, b), axis=0)
r2 = np.concatenate((a, b), axis=1)
r3 = np.concatenate((a, b), axis=2)
print(r1, r1.shape)
print(r2, r2.shape)
print(r3, r3.shape)

# TODO 矩阵的分隔
# TODO np.split(ary, indices_or_sections, axis)
# ! ary -- 被分隔的矩阵
# ! indices_or_sections -- 如果是一个整数，就用该数平均分隔，如果是一个范围，则沿轴切分

a = np.arange(1, 13)
r = np.split(a, 3)
print(a)
print(r)

r = np.split(a, [4, 6])
print(r)

a = np.arange(1, 17).reshape(4, 4)
print(a)
r = np.split(a, 2, axis = 0)
print(r)
r1 = np.split(a, 2, axis = 1)
print(r1)

r, w, k  = np.split(a, [2, 3], axis = 0)
print(r)
print(w)
print(k)

r, w, k  = np.split(a, [2, 3], axis = 1)
print(r)
print(w)
print(k)

# TODO np.hsplit(ary, indices_or_sections)水平方向分隔
# TODO np.vsplit(ary, indices_or_sections)垂直方向分隔

# TODO 矩阵的转置
# TODO np.transpose()
a = np.arange(1, 13).reshape(4, 3)
print(a)
b = a.transpose()
print(b, b.shape)

# TODO ndarray.T -- 同样实现转置
print(a.T, a.shape)

# ! 对于三维矩阵，默认的转置是将i和k转置，但是transpose可以指定转置
# ! 对于矩阵，维度的表示从0开始分别对应
a = np.arange(1, 25).reshape(2, 3, 4)
b = np.transpose(a, (1, 2, 0))
print(a, a.shape)
print(b, b.shape)


