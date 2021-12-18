#!/bin/bash
echo "Menu"
echo "1. Vi"
echo "2. Nano"
echo "3. Links"
echo "4. Exit"
read num
if [ $num = "1" ]
then vi
elif [ $num = "2" ]
then nano
elif [ $num = "3" ]
then links
elif [ $num = "4" ]
then exit
else echo "ERROR"
fi