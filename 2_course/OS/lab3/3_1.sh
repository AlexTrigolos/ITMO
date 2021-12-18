#!/bin/bash
_date=$(date +"%d-%m-%y___%H:%M:%S")
mkdir ~/test && { echo "catalog test was created successully" > ~/report ; touch ~/test/$_date ; }
ping -c1 www.net_nikogo.ru || echo "${_date} ping error" >> ~/report