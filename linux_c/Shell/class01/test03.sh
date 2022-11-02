#!/bin/env bash

# 判断一个进程(httpd)是否存在
# 使用命令pgrep

pgrep httpd &> ./null1
if [ $? -ne 0 ]; then
	echo "当前httpd进程不存在"
else
	echo "当前httpd进程存在"
fi


