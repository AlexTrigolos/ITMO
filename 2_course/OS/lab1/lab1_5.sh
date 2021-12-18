#!/bin/bash
awk '/INFO/ {print $0}' /var/log/anaconda/syslog > info.log