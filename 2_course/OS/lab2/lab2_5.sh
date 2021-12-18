#!/bin/bash
ppid_0="0"
ART_sum="0"
count="0"
AVG="0"
echo -e "$(<out2_4.txt)\n" | sed "s/[^0-9.]\+/ /g" | sed "s/^ //g" |
while read str
do
	pid=$(awk '{print $1}' <<< $str)
	ppid=$(awk '{print $2}' <<< $str)
	ART=$(awk '{print $3}' <<< $str)
	if [[ $ppid == $ppid_0 ]]
	then
		ART_sum=$(echo "$ART_sum+$ART" | bc | awk '{printf "%f", $0}')
		count=$(($count+1))
	else
		AVG=$(echo "scale=5; $ART_sum/$count" | bc | awk '{printf "%f", $0}')
		echo "Average_Children_Running_Time_of_ParentID="$ppid_0" is "$AVG
		ART_sum=$ART
		count=1
		ppid_0=$ppid
	fi
	if [[ ! -z $pid]]
	then
		echo "ProcessID="$pid" : Parent_processID="$ppid" : Average_Running_Time="$ART
	fi
done > out2_5.txt