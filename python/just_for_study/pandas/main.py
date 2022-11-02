import pandas as pd
import numpy as np

# 常用数据类型
# Series 一维，带标签(索引)数组
# DataFrame 二维，Series容器
a = pd.Series([1, 2, 3, 4, 5, 6, 7, 8, 9, 0])
print(a)
print(type(a))

# 可以指定索引使用index,但是需要注意，索引的数量要和元素的个数匹配
b = pd.Series([1, 2, 3], index = list([3, 2, 1]))
print(b)

# 可以使用字典来快捷自定义索引
t_dict = {"name" : "lily", "age" : 18, "tel" : 10086}
c = pd.Series(t_dict)
print(c)

# 修改元素默认类型dtype
d = pd.Series([1, 2, 3], dtype = float)
print(d)
print(d.dtype)

# pandas依旧也有切片索引的操作
print(a[ : : 2])

# pandas的内置属性index, values
print(d.index)
print(d.values)

# 可以使用index配合for循环
for i in a.index :
    print(i)

# where方法, where(condition1, condition2)如果条件一满足，就不变，如果不满足，就设置为条件二
a = pd.Series(range(10))
print(a.where(a > 5, 10))

# DataFrame
a = pd.DataFrame(np.arange(12).reshape(3, 4))
print(a)
print(type(a))

# 行索引，横向索引，index， 0轴， axis = 0
# 列索引，纵向索引，colnumns， 1轴， axis = 1
b = pd.DataFrame(np.arange(12).reshape(3, 4), index = list([3, 2, 1]), columns = list([4, 3, 2, 1]))
print(b)

# 在DataFrame中使用字典初始化，需要使用key对应列表var
# 默认是字典作为列来显示
c = pd.DataFrame({"name" : ["lily", "hehe"], "age" : [18, 20]})
print(c)

# 如果要分开写字典，那么必须用列表形式
d = pd.DataFrame([{"name" : "lily", "age" : 18}, {"name" : "hehe", "age" : 20}])
print(d)

'''
    DataFrame的基本属性
    df.shape            --- 行数，列数
    df.dtype            --- 列数据类型
    df.ndim             --- 数据维度
    df.index            --- 行索引
    df.columns          --- 列索引
    df.values           --- 对象值
    
    DataFrame整体情况查询
    df.head(n)          --- 显示从头的第几行，默认为5行
    df.tail(n)          --- 显示从尾的第几行，默认为5行
    df.info()           --- 相关信息概览，行数，列数，列索引，列非空值个数，列类型，行类型，内存占用
    df.describe()       --- 快速综合统计结果：计数，均值，标准差，最大值，四分位数，最小值
'''

df = pd.DataFrame({"name" : ["lily", "hehe"], "age" : [18, 20]})
print(df.index)
print(df.columns)
print(df.dtypes)
print(df.ndim)
print(df.shape)

print(df.head())
print(df.tail())
print(df.info())
print(df.describe())

# DataFrame中的排序方法sort_values(by = , ascending = )
# by = "key"指定用什么标准来排序，ascending = True就是升序

# DataFrame的索引df[使用切片][使用字符串]
# df.loc(row, col) 通过标签索引行数据
# df.iloc 通过位置获取行数据
t = pd.DataFrame(np.arange(12).reshape(3, 4), index = list("abc"), columns = list("WXYZ"))
print(t)
print(t.loc["a"])
print(t.loc[["a", "c"]])

print(t.iloc[1])

# DataFrame的索引可以使用bool
'''
    在 pandas中常用的字符串操作
    .str.contains           --- 返回表示各字符串是否含有指定模式的bool
    .str.len                ---计算各字符串的长度
    .str.lower              --- 转换小写
    .str.upper              --- 转换大写
    .str.replace            --- 用指定字符串 替换找到的格式
    .str.split              --- 根据分隔符或者正则表达式对字符串进行拆分 
'''

# 对于pandas中数据的缺失数据的处理
# pd.isnull(df), pd.notnull(df) --- 判断数据是否为NaN
# 处理方式一：直接删除所在行列 dropna(axis = 0, how =  "any", inplace = False)
# 处理方式二：填充数据，pd.fillna(t.mean()), pd.fiallna(pd.median()), pd.fillna(0)
# 处理数据为0的方法：pd[i == 0] = np.nan+