#!/bin/bash
ps aux | sort -nkr9 | head -1 | awk '{print $2" : " $9}'