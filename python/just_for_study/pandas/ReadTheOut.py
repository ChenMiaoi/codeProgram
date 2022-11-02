import pandas as pd

# 对于外部数据，pandas内置了一些接口
# 比如对于csv文件，直接pd.read_csv()
# 比如对于mysql, 直接pd.read_sql()
# 比如对于html, 直接pd.read_html()
FILE_PATH = "./dogNames2.csv"
df = pd.read_csv(FILE_PATH)
print(df.info())

# 排序 -- DataFrame中排序的方法df.sort_values()，默认是升序
df = df.sort_values(by = "Count_AnimalName", ascending = False)
print(df)

# DataFrame的索引
print(df[:20])
print(df[:20]["Row_Labels"])

# bool索引 -- 使用操作符而不要使用 and or  not
print(df[(df["Count_AnimalName"] > 800) & (df["Count_AnimalName"] < 1000)])