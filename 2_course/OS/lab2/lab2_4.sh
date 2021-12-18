#!/bin/bash
for pid in $(ps -Ao pid | tail -n +2)
do
	file="/proc/"$pid
	ppid=$(grep -Ehsi "ppid" $file"/status" | grep -o "[0-9]\+")
	sum_exec_runtime=$(grep -Ehsi "se\.sum_exec_runtime" $file/sched | awk '{print $3}')
	nr_switches=$(grep -Ehsi "nr_switches" $file/sched | awk '{print $3}')
	if [ -z $ppid ]
	then
		ppid=0
	fi
	if [ -z $sum_exec_runtime ] || [ -z $nr_switches ]
	then
		ART=0
	else
		ART=$(echo "scale=5; $sum_exec_runtime/$nr_switches" | bc | awk '{printf "%f", $0}')
	fi
	echo "$pid $ppid $ART"
done | sort -nk2 | awk '{print "ProcessID="$1" : Parent_ProcessID="$2" : Average_Running_Time="$3}' > out2_4.txt