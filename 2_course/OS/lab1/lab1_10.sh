#!/bin/bash
man bash | grep -oi "[[:alpha:]]\{4,\}" | tr [:upper:] [:lower:] | sort | uniq -c | sort -nr | head -3