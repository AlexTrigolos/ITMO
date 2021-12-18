#!/bin/bash
backupParentDir="$HOME/"
sourceDir="$HOME/source/"
if [[ ! -d sourceDir ]]
then
	echo "source dir wasn't created"
	exit 1
fi
todayDate=$(date "+%F")
created=0
backupPrefix="Backup-"
backupReport="$HOME/backup-report"
lastBackupDate=$(ls ~ | grep -E "^Backup-" | sort -n | tail -1 | sed "s/Backup-//")
todaySec=$(date --date=$todayDate "+%s")
lastbackupDir=$(ls $backupParentDir -1 | grep -E "Backup-[0-9]{4}-[0-9]{2}-[0-9]{2}" | sort -r -k2 | head -1)
lastbackupSec=$(date --date=$(ls $backupParentDir -1 | grep -Eo "Backup-[0-9]{4}-[0-9]{2}-[0-9]{2}" | sort -r -k2 | head -1 | sed "s/^Backup-//") "+%s")
let dateDiff=($todaySec-$lastbackupSec)/60/60/24

if (( $dateDiff > 7 )) || [[ -z "$lastBackupDate" ]]
then
mkdir $backupParentDir$backupPrefix$todayDate
currentbackupDir=$backupParentDir$backupPrefix$todayDate"/"
echo "backup created on "$todayDate" in directory "$sourceDir" Files Copied :" >> $backupReport
	for file in $(ls $sourceDir -1)
	do
	cp $sourceDir$file $currentbackupDir$file
	echo $file >> $backupReport
	done
else
currentbackupDir=$backupParentDir$lastbackupDir"/"
echo "Updating backup in directory "$currentbackDir". Date: "$todayDate"." >> $backupReport

for file in $(ls $sourceDir -1)
do
currentfile=$currentbackupDir$file
if [ -f $currentfile ]
then
source_size=$(stat $sourceDir$file -c%s)
actual_size=$(stat $currentfile -c%s)
	if [[ "$source_size" != "$actual_size" ]]
	then
	mv $currentfile $currentfile"."$todayDate
	cp $sourceDir$file $currentfile
	echo "New version of file "$file" found. Old version moved to "$file.$todayDate"." >> $backupReport
	fi
else
cp $sourceDir$file $currentfile
echo "New file "$file" copied" >> $backupReport
fi
done
fi	