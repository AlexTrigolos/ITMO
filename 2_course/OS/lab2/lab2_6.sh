#!/bin/bash
grep "VmRSS" /proc/*/status | sed "s/[^0-9.]\+/ /g" | sed "s/^ //" | sort -nrk2 | head -1
top -o RES | head -8 | tail -n +8 | awk '{print $2" "$7}'