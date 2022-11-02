#!/bin/env bash

sum=0
i=2
while [ $i -le 50 ]
do
	let sum+=i
	let i+=2
done
echo "50以内的偶数和为：$sum"
