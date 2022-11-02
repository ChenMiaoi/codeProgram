#!/bin/env bash

read -p "请输入您想要更改的用户：" user;
if [ "$user" != "" ]; then
	read -sp "请输入您想要更改的密码：" passwd1;
	echo
	read -sp "请重复您想要更改的密码：" passwd2;
	echo
	if [ "$passwd1" = "$passwd2" ]; then
		echo "密码修改成功，请妥善保管！"
	else
		echo "两次密码不一致，请重新确认！(已退出，错误码"$?")"
	fi
fi
