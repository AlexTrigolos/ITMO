#!/bin/bash
file="$PWD/$1"
trash=$HOME/.trash
log=$HOME/trash.log

if [[ $# != 1 ]]
then
	echo "Need only one argument."
	exit 1
fi

if [[ ! -f $file ]]
then
	echo "Invalid filename."
	exit 1
fi

if [ ! -d $trash ]
then
	mkdir $trash
	touch $log
fi

dat=$(date +"%s")
ln "$file" "$trash/$dat"
rm "$file"
echo "$file:$dat" >> $log