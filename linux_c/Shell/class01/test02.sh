#!/bin/env bash

# 判断两台主机是否ping通
# 1. 使用ping -c的命令
# 2. 根据命令的执行结果状态来判断是否ping通
# 3. 根据逻辑和语法来编写脚本

# 交互式定义变量， 让用户自己决定ping哪个主机
read -p "请输入您要ping的主机IP：" ip

# 使用ping,判断主机是否ping互通
ping -c1 $ip &> ./null
if [ $? -eq 0 ]; then
	echo "当前主机<127.0.0.1>与远程主机<$ip>是互通的"
else
	echo "当前主机<127.0.0.1>与远程主机<$ip>是互通的"
fi
