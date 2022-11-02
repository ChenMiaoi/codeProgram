# Shell

---  

## 文本处理工具

### grep

> grep是行过滤工具，用于根据 关键字进行过滤


``` linux
# grep [option] 'keyworkd' filename
```

- 常见选项
	- i：忽略大小写
	- v：查找不包含指定内容的行 ，反向选择
	- w：按单词搜索
	- o：打印 匹配关键字
	- c：统计匹配到的次数
	- n：显示行号
	- r：逐层遍历目录查找
	- A：显示匹配行及后面多少行
	- B：显示匹配行及前面多少行
	- C：显示匹配行及前后多少行
- 关键字
	- ^key：以该关键字开头的行
	- key$：以该关键字结尾的行

> **一般情况下，将grep自动添加上--color=auto显示关键字高亮会使得效率更高，更不容易出错** 

```linux
# vim /etc/bashrc(或者vim .bashrc)
# 进入文件后，直接在文件最后一行插入
# alias grep = 'grep --color=auto'
# :wq
```

### cut

> cut是列截取工具，用于列的截取

```linux
# cut [option] filename
```

- 常见 选项
	- c：以字符为单位进行分割，截取
	- d：自定义分隔符，默认为制表符\\t
	- f：与-d选项一起使用，指定截取哪一块区域

- 案例：

```linux
# cut -d: -f1,6,7 test.txt
以冒号为分割符，截取第1,6,7列的内容
```

### sort

> sort用于排序，它将文件的每一行作为一个单位，从首字母向后，依次按照ASCII码进行比较，最后将他们按升序输出

```
# sort [option] filename
```

- 常见选项
	- u：去除重复行
	- r：降序排列，默认是升序
	- o：将排序的结果输出到文件中，类似输出重定向
	- n：以数字排序，默认是按字符排列
	- t：分隔符
	- k：第N行
	- b：忽略前导空格
	- R：随即排序

### uniq

> uniq用于去除连续的重复行

```linux
# uniq [option] filename
```

- 常用选项
	- i：忽略大小写
	- c：统计重复行次数
	- d：只显示重复行

### tee

> tee从标准输入读取并且写入到标准输出和文件，即：双向覆盖重定向(屏幕输出|文本输入)

```linux
# echo hello | tee filename
```

- 常用选项
	- a：双向追加重定向


### diff

> diff工具用于逐行比较文件的不同
> 	注意：**diff描述两个文件不同的方式是告诉我们怎样改变第一个文件之后与第二个文件匹配** 

```linux
# diff [option] filename1 filename2
```

- 常用选项
	- b：不检查空行
	- B：不检查空白行
	- i：不检查大小写
	- w：忽略所有空格
	- c：上下文格式显示
	- u：合并格式显示
	- --normal：正常格式显示(默认)

### paste

> paste用于合并文件行

```linux
# paste [option] filename
```

- 常用选项
	- d：自定义间隔符，默认是tab
	- s：串行处理，非并行

### tr

> tr用于字符 转换，替换和删除。主要用于 删除文件中控制字符或进行字符转换

- 常用选项
	- d：删除string1中的所有输入字符
	- s：删除所有重复出现字符序列，只保留第一个。即将重复出现字符串压缩为一个字符串

- 案例：

```linux
用法1：命令的执行结果交给tr处理，其中string1用于查询，string2用于转换处理
# comands  | tr 'string1' 'string2'

用法2：tr处理的内容来自文件，记住要使用"<"标准输入
# tr 'string1' 'string2' < filename

用法3：匹配string1进行相应操作，如删除操作
# tr option  'string1' < filename
```


