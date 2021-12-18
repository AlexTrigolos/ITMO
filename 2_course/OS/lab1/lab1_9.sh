#!/bin/bash
find /var/log/* -name '*.log' | xargs wc -l | sort -nr | awk '{print "Total is: ", $1}' | head -1