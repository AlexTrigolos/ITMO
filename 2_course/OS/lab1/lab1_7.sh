#!/bin/bash
email="[0-9A-Za-z._]\+@[0-9A-Za-z.]\+\.[0-9a-zA-Z.]\+"
list=$(grep -R $email /etc | grep -o $email)
echo $list | sed 's/ /, /g' > email.lst