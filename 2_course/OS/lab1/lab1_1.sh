#!/bin/bash
max=0
echo "Enter a "
read a
echo "Enter b "
read b
echo "Enter c "
read c
if [ $a -gt $b ]
then
max=$a
else
max=$b
fi
if [ $c -gt $max ]
then
max=$c
fi
echo "Max = $max"