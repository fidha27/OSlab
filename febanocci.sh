#!/bin/bash

echo "Febonocii series"

echo "Enter the no of terms"
read n
echo "Series are"

a=0
b=1

for((i=0;i<n;i++))
do
        echo "$a"
        r=$(($a+$b))
        a=$b
        b=$r

done
