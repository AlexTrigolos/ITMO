#!bin/bash
echo "Enter string "
read str
declare -a arr
i=0
while [ $str != "q" ]
do
	arr[$i]=$str
	#echo "${arr[$i]}"
	i=$(( $i + 1 ))
	echo "Enter string "
	read str
done
echo ${arr[@]}
unset arr