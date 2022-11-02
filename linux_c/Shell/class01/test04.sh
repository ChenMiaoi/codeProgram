#!/bin/env bash

# 用于时间同步
# 每隔30s同步一次

NTP=10.1.1.1
count=0
while true
do 
	ntpdate $NTP &> ./null2
	if [ $? -ne 0 ]; then
		echo "System data failed" | mail -s "Check System Data" root@localhost
	else
		let count++
		if [ $count -eq 100 ]; then
			echo "System data success" | mail -s "Ceck System Data" root@localhost && count=0
		fi
	fi
	sleep 30
done
