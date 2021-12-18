#!/bin/bash
./3_4_dop.sh&pid0=$!
./3_4_dop.sh&pid1=$!
./3_4_dop.sh&pid2=$!
renice -n 10 -p $pid0
#kill pid2
at now + 1 minute <<< "kill ${pid0}; kill ${pid1}"