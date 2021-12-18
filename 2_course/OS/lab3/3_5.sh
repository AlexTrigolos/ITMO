#!/bin/bash
mkfifo pipe
./3_5_p.sh&
./3_5_g.sh
rm pipe