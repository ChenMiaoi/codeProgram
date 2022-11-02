import matplotlib.pyplot as plt
import numpy as np
# TODO 绘制基础
'''
    plt.title()                         --设置图表名称
    plt.xlabel()                        --设置x轴名称
    plt.ylabel()                        --设置y轴名称
    plt.xticks(x, ticks, rotation)      --设置x轴的刻度，rotation旋转角度
    plt.yticks()                        --设置y轴的刻度
    plt.plot()                          --绘制线性图表
    plt.show()                          --显示图表
    plt.legend()                        --显示图例
    plt.text(x, y, test)                --显示每条数据的值，x,y值的位置
    plt.figure(name, figsize = (w, h), dpi = n)     --设置图片大小
'''

# TODO 绘制两个点(1,2) (4,8)
# ! plot的参数x和y分别放在一起，使用列表
plt.plot([1, 4], [2, 8])
plt.show()

x = [1, 2, 3, 4, 5]
y = [1, 4, 9, 16, 25]
plt.plot(x, y)
plt.show()

# TODO 设置样式
# ! 参数 linewidth = n设置线条宽度
# ! 在title中使用中文会出现编码错误 -- plt.rcParams['font.sans-serif'] = ['SimHei']
x = [1, 2, 3, 4, 5]
y = [1, 4, 9, 16, 25]
plt.plot(x, y, linewidth = 2)

plt.xlabel('x', fontsize = 14)
plt.ylabel('y = x^2', fontsize = 14)
plt.title("ZheXianTu", fontsize = 24)
plt.show()

# ! 参数fontsize = n设置字体大小

# TODO plt.savefig() # ! 默认的格式png可以指定格式
x = range(-100, 100)
y = [i**2 for i in x]
plt.plot(x, y)
plt.savefig("result.jpg")
plt.show()

x = np.linspace(0, 10, 100)
y = np.sin(x)
plt.plot(x, y)

x = np.linspace(0, 10, 100)
y = np.cos(x)
plt.plot(x, y)

x= np.linspace(0, 10, 100)
y = np.tan(x)
plt.plot(x, y)
plt.savefig("sin_cos_tan.jpg")
plt.show()

# TODO 使用plt.subplot()将画布分区
# TODO 使用plt.xlim() 或者 plt.ylim()修改x，y轴的坐标
x = np.linspace(1, 10, 100)
plt.subplot(2, 2, 1) # ! 两行两列第一分区
plt.title('sin(x)')
plt.plot(x, np.sin(x))
plt.subplot(2, 2, 2)
plt.title('cos(x)')
plt.plot(x, np.cos(x))
plt.subplot(2, 2, 3)
plt.title('tan(x)')
plt.plot(x, np.tan(x))
plt.subplot(2, 2, 4)
plt.title('cot(x)')
plt.plot(x, 1 / np.tan(x))
plt.show()