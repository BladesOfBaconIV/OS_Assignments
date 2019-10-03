#! /bin/bash
# ID: 16160703
# Lorcan Williamson

# File info part
ls -l --sort=size ~ > tempfile
biggest_file=$(grep -m 1 '^-.*' tempfile | awk '{print $9}')
num_files=$(grep '^-.*' tempfile | wc -l)
num_dir=$(grep '^d.*' tempfile | wc -l)
echo "Biggest file: $biggest_file"
echo "Number of files: $num_files"
echo "Number of diectories: $num_dir"
rm tempfile

# Free blocks
df ~ | tail -n 1 > temp
vim temp
info=($(cat temp)) # An array for holding the df info
echo "Free space: ${info[3]}"
echo "Percent used: ${info[4]}"
if [ "${info[3]}" -lt 5000000 ];
    then
	echo "Disk space is running low, ${info[3]} used"
fi
rm temp
