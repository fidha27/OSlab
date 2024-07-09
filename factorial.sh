#!/bin/bash

echo "Factorial Numbers"

echo "Enter the no"
read n

echo "Factorial of $n is"
 fact=1
for((i=1;i<=n;i++))
do
        fact=$((fact*i))
done
echo $fact
