from turtle import color
import matplotlib.pyplot as plt
import numpy as np

# TODO 使用plt.bar()绘制柱状图,参数width = n设置宽度
x = [1980, 1985, 1990, 1995]
y = [1000, 3000, 4000, 2000]
x_label = ['1980s', '1985s', '1990s', '1995s']
# TODO 使用plt.xticks()修改x轴坐标名称
plt.bar(x, y, width = 2)
plt.xticks(x, x_label)
plt.xlabel('year')
plt.ylabel('sole')
plt.title('according to the sole')
plt.show()

# TODO 使用plt.barh()绘制水平方向柱状图 
x = np.arange(5)
y = np.random.randint(-5, 5, 5)
plt.subplot(1, 2, 1)
plt.bar(x, y, color = 'blue')

plt.subplot(1, 2, 2)
plt.barh(x, y, color = 'red')
plt.show()