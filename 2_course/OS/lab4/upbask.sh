#!/bin/bash
if [[ ! -d ~/restore ]]
then
mkdir ~/restore
else
rm -r ~/restore
mkdir ~/restore
fi

latestBackupDate=$(ls ~ | grep -E "^Backup-" | sort -n | tail -1 | sed 's/^Backup-//')

if [[ -z "$latestBackupDate" ]]
then
	echo "No any backup."
	exit 1
fi

lastBackup="$HOME/Backup-${latestBackupDate}"
for file in $(ls $lastBackup | grep -Ev "\.[0-9]{4}-[0-9]{2}-[0-9]{2}$")
do
	cp "${lastBackup}/${file}" "$HOME/restore/${file}"
done	