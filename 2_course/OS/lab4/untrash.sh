#!/bin/bash
resFile=/home/user/lab4/$1
if [[ $# != 1 ]]
then
	echo "Tncorrect argumens."
	exit 1
fi

if [[ ! -d ~/.trash ]]
then
	echo "Trash dir wasn't created."
	exit 1
fi

if [[ ! -f ~/.trash.log ]]
then
	echo "Trash.log file wasn't created."
	exit 1
fi

if [[ -z $(grep "$1" ~/.trash.log) ]]
then
	echo "$1 doesn't exist."
	exit 1
fi

for i in $(grep -h $1 $HOME/.trash.log)
do
Path=$(echo $i | awk -F ":" '{print $1}')
File=$(echo $i | awk -F ":" '{print $2}')

if [[ $resFile == $Path ]]
then
rmFile=$HOME/.trash/$File
	if [ -e $rmFile ]
	then
	echo "Do you want to restore file - $Path ?"
	read ans
		if [[ $ans == "yes" ]]
		then
			if [ -d $(dirname $Path) ]
			then
				if [[  -e $Path ]]
				then
					echo "Dublicate!"
					read newName
					ln "$rmFile" "$HOME/lab4/$newName"
					rm $rmFile
				else
					ln "$rmFile" "$Path"
					rm $rmFile
				fi
			else
			echo "$(dirname $Path) has been removed!"
			ln "$rmFile" "$HOME/$1"
			rm $rmFile
			fi
		grep -v $File $HOME/.trash.log > $HOME/.trash0.log
		mv $HOME/.trash0.log $HOME/.trash.log
		fi
	fi
fi
done	