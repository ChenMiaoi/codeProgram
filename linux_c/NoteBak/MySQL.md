# MySQL  

---  

## MySQL前期准备

### 链接MySQL  

```mysql
mysql -h 127.0.0.1 -P 3306 -u root -p
```

- h : 链接那一台主机
- P : 端口号(默认3306)
- u : user
- p : 

## MySQL命令

- 创建数据库

```mysql
create database name;
```

> 创建数据库的本质就是在数据库路径下创建一个目录

- 创建表

```mysql
create table if not exists name(
	...,
	...
);
```

> 创建表的本质就是在指定数据库路径下创建一个普通文件

- 删除库

```mysql 
drop database name;
```

- 查看表

```mysql
desc table_name;
```

- 插入操作

```mysql
insert into table_name (key1, key2, ...) values (var1, var2, ...);
```

- 查询表

```mysql
select * from table_name;
```


### 库的操作

#### 创建数据库

```mysql
create database [if not exists] db_name [create_specification [, create_specification] ...];
```

> []是可选项  
> character set指定数据库采用的字符集
> collate指定数据库字符集的校验规则
> 

- 案例：

```mysql
create database db1 charset=utf8 collate utf8_general_ci

# 可以使用show charset查看字符集
# 可以使用show collation查看字符集校验规则
```

- 注：
	- utf8_general_ci不区分大小写
	- utf8_bin区分大小写

---  

#### 查看数据库

```mysql
show databases;
```

#### 查看创建数据库

```mysql
show create database db_name;
```

#### 修改数据库

```mysql
alter database db_name [alter_spacification [,alter_spacification] ...]
```

- 案例：将数据库的字符编码改为gbk

```mysql
alter database db_name charset=gbk;
```

#### 删除数据库

```mysql 
drop database [if exists] db_name;
```

- 注意：
	- 删除之后，对应的数据库文件夹被删除，级联删除，里面的数据表也会被删除

#### 数据库备份

```mysql
mysqldump -P 3306 -u root -p -B db_name > 数据库备份存储的文件路径
```

> 所谓的备份，本质上是将历史上对mysql指定的数据库的所有历史操作都做备份
> mysql怎么记录呢？
>> binlog, 全量记录对指定数据库的所有操作

- 案例：

```mysql
mysqldump -P 3306 -u root -p -B mytest > \home\user\mytest.sql
```

#### 数据库还原

```mysql
[mysql]> source ./mytest.sql
``` 

- 注意：
	- 如果想要备份数据表

```mysql
mysqldump -u root -p db_name table_name1 tabale_name2 > \home\user\mytest.sql
```

- 如果没有带上-B参数，在恢复的时候，需要先创建空数据库，然后使用数据库，再使用source来还原

#### 查看链接情况

```mysql
show processlist
```

### 表操作

#### 创建表

```mysql
create table table_name(
	field datatype,
	field datatype,
	...
)character set 字符集 collate 校验规则 engine 存储引擎;
```

- 说明
	- field表示列名
	- datatype表示列的类型
	- character set 字符集，如果没有指定的字符集，则以所在数据库的字符集为准
	- collate 校验规则，如果没有指定的校验规则，则以所在的数据库的校验规则为准

- 案例：

```mysql
create table users(
	id int,
	name varchar(20) comment '用户名',
	passwd char(32) comment '密码是32位的md5值',
	birthday date comment '生日'
)character set utf8 engine MyISAM;
```

- 说明
	- comment是对于列的注释
	- 不同的存储引擎，创建表的文件不一样
	- users表存储引擎是MyISAM,在数据目中有三个不同的文件，分别是：
		- users.frm：表结构
		- users.MYD：表数据
		- users.MYI：表索引


#### 查看表

```mysql
desc table_name;
show create table table_name;
```

![[Pasted image 20220703155328.png]]  

- 说明：
	- Field：每一列的列属性
	- Type：每一列的类型
	- Null：是否允许为空，属于约束的一种
	- Key：索引类型
	- Default：默认缺省值
	- Extra：扩充

#### 修改表

```mysql
alter table table_name add (column datatype [default expr] [, column datatype]...);
alter table table_name modify (column datatype [default expr] [, column datatype]...);
alter table table_name drop (column);
alter table table_name rename new_name; #修改表名
alter table table_name change column_name 
new_column
```

- 建议：
	- 在构建表结构的时候就把所需要的属性建立完毕，尽量减少使用alter
	- after：指定添加列位置，在什么之后

#### 删除表

```mysql
drop table table_name;
```


### 数据类型

| 分类 | 数据类型 | 说明 | 
| --- | --- | --- | 
| --- | bit(M) | 位类型。M指定位数，默认为1,范围1-64 |  
| --- | tinyint(unsigned) | 带符号的范围-128～127,无符号范围0～255 | 
| --- | bool | 使用0和1表示真和假 | 
| 数值 | samllint(unsigned) | 带符号是-2^15到2^15-1,无符号是2^16-1 |
|  | int(unsigned) | 带符号是-2^31到2^31-1,无符号是2^32-1 | 
| 类型 | bigint(unsigned) | 带符号是-2^63到2^63-1,无符号是2^64-1 |
| --- | float[(M, D)] (unsigned) | M指定显示长度，d指定小数位数，占用4字节 |
| --- | double[(M, D)] (unsigned) | 表示比float精度更大的数，占用8字节 |
| --- | decimal(M, D) (unsigned) | 定点数M指定长度，D表示小数点的位数 |
| --- | char(size) | 固定长度字符串，最大255 | 
| 文本 | varchar(size) | 可变长度字符串，最大长度65535 | 
| 二进制类型 | blob | 二进制数据 | 
| --- | text | 大文本，不支持全文索引，不支持默认值 |
| 日期类型 | date/datetime/timestamp | 日期类型(yyyy-mm-dd)(yyyy-mm-dd hh:mm:ss) timestamp时间戳 | 
| String | enum类型 | enum是一个字符串对象，其值来自表创建时在列规定中显示枚举的一个常量 | 
| 类型 | set类型 | set是一个字符串对象，可以有零个或多个值，其值来自于表创建时规定允许的一列值。指定包括多个set成员的set列值时各成员之间用逗号间隔开。因此，set成员本身不能包含逗号 |

> MySQL对于数据具有更严格的 规则，叫做约束。
> MySQL数据类型本身，就是一种约束


### 约束

