#!/bin/bash
var="+"
x=1
(tail -f pipe) |
while true
do
	read line
	case "$line" in
		"+")
			var="$line"
			echo "summ"
		;;
		"*")
			var="$line"
			echo "mult"
		;;
		"QUIT")
			killall tail
			echo "quit"
			exit 0
		;;
		[0-9]*)
			case $var in
				"+")
					x=$(echo "${x}+${line}" | bc)
					echo $x
				;;
				"*")
					x=$(echo "${x}*${line}" | bc)
					echo $x
				;;
			esac
		;;
		*)
			killall tail
			echo "Not normal"
			exit 1
		;;
	esac
done