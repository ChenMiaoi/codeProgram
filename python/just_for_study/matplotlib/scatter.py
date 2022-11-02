import matplotlib.pyplot as plt
import numpy as np

# TODO plt.scatter()绘制散点图
# ! 但是plot中的参数'o'表示点状也可以绘制散点图
x = np.linspace(0 ,10 ,100)
plt.scatter(x, np.sin(x))
plt.show()

'''
    使用plot绘制图形的速度优于scatter，如果画一堆点，而且点的形式没有差别
    那么我们使用plot，如果点的形式(颜色，形状)有差别，则必须使用scatter
'''

np.random.seed(0)
x = np.random.rand(100)
y = np.random.rand(100)
size = np.random.rand(100) * 100
color = np.random.rand(100)
plt.scatter(x, y, s = size, c = color, alpha = 0.75)
# ! 参数s = n表示点的size
# ! 参数c = n表示点的color
# ! 参数alpha = n表示点的透明度
# ! 注意：颜色参数的个数和大小参数的个数必须和点的个数相同
plt.show()