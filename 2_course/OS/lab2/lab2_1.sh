#!/bin/bash
proc=$(ps -aU user -o pid,command | tail -n +2 | sed -r "s/\*([^ ]+)\s(.*)/\1:2/")
lines=$(echo "$proc" | wc -l)
echo "Count: $lines" > out2_1.txt
echo "$proc" >> out2_2.txt