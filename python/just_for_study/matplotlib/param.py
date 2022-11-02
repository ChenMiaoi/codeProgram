import matplotlib.pyplot as plt
import numpy as np

# TODO plot参数 -- 样式
'''
    '-'             --实线
    '--'            --短横线
    '-.'            --点划线
    ':'             --虚线
    '.'             --点标记
    ','             --像素标记
    'o'             --圆标记
    'v'             --倒三角标记
    '^'             --正三角标记
    '1'             --下箭头标记
    '2'             --上箭头标记
    '3'             --左箭头标记
    '4'             --右箭头标记
    's'             --正方形标记
    'p'             --五边形标记
    '*'             --星形标记
'''

# TODO plot参数 -- 颜色
'''
    'b'             --蓝色
    'g'             --绿色
    'r'             --红色
    'c'             --青色
    'm'             --品红色
    'y'             --黄色
    'k'             --黑色
    'w'             --白色
'''
# ! 可以同时组合
x = np.linspace(0, 10, 100)
plt.plot(x, x + 0, label = '-b')
plt.plot(x, x + 1, label = '--g')
plt.plot(x, x + 2, label = '-.r')
plt.plot(x, x + 3, label = ':c')
plt.plot(x, x + 4, label = ',m')
plt.plot(x, x + 5, label = 'oy')
plt.plot(x, x + 6, label = 'vk')
plt.plot(x, x + 7, label = '^w')
plt.plot(x, x + 8, label = '1b')
plt.plot(x, x + 9, label = '2g')
plt.plot(x, x + 10, label = '3r')
plt.plot(x, x + 11, label = '4c')
plt.plot(x, x + 12, label = 'sm')
plt.plot(x, x + 13, label = 'py')
plt.plot(x, x + 14, label = '*k')
plt.legend(loc = 'upper right')
# ! 默认的位置在左上角，可以通过loc参数修改
# TODO 使用plt.legend()添加图例，给plot添加参数label
plt.show()

# TODO plt.legend参数
'''
    loc             --图例位置
    fancybox        --边框
    framealpha      --透明度
    shadow          --阴影
    borderpad       --边框宽度
'''