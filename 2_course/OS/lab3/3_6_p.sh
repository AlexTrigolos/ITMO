#!/bin/bash
var="+"
x=1
sig() {
	echo "quit"
	exit 0
}
ur1() {
	var="+"
}
ur2() {
	var="*"
}
trap 'sig' SIGTERM
trap 'ur1' USR1
trap 'ur2' USR2
while true
do
	case "$var" in
		"+")
			x=$(echo "${x} + 2" | bc)
		;;
		"*")
			x=$(echo "${x} * 2" | bc)
		;;
	esac
	echo $x
	sleep 2
done