#!/bin/bash
> out2_7_1.ps
> out2_7_2.ps
path=$(ls /proc | awk '$0 !~ /[A-Za-z]/')
processes=$(echo $path | tr " " "\n")
for pid in $processes
do
	if[ -f /proc/$pid/io ]
	then
		echo $pid" "$(grep "read_bytes:" "/proc/"$pid"/io" | awk '{print $2}') >> out2_7_1.ps
	fi
done
sleep 1m
for pid in $processes
do
	if[ -f /proc/$pid/io ]
	then
		echo $pid" "$(grep "read_bytes:" "/proc/"$pid"/io" | awk '{print $2}') >> out2_7_1.ps
	fi
done
cat out2_7_1.ps |
while read str
do
	pid=$(awk '{print $1}' <<< str)
	first=$(awk '{print $2}' <<< str)
	second=$(cat out2_7_2.ps | awk -v pid="$pid" '{if ($1 == pid) print $2}')
	diff=$(echo "$second-$first" | bc)
	cmd=$(ps -q $pid -o comm=)
	echo $pid" : "$cmd" : "$diff
done | sort -t ':' -nrk3 | head -3
rm *.ps