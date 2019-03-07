#! /bin/bash
# ID: 16160703
# Name Lorcan Willamson

# Current user/machine info
echo "Current user is $USER (ID: $UID)"
echo "Current machine hostname: $HOSTNAME"
echo "Current machine type: $MACHTYPE"
echo # Blank line for formatting
# Part 2
df -h >> disk_info
num_disk=$(tail -n +2 disk_info | wc -l)
home_avail=$(grep "home" disk_info | awk '{print $4}')
home_perc=$(grep "home" disk_info | awk '{print $5}')
echo "There are $num_disk volumes on the system"
echo "There is $home_avail free space in home directory ($home_perc used)"
rm disk_info
# Part 3
echo "CPU info:"
echo "    $(grep "model name" /proc/cpuinfo)"
echo "    $(grep "cpu MHz" /proc/cpuinfo)"
echo "    $(grep "cache size" /proc/cpuinfo)"
# Part 4
echo "Memory info:"
echo "    $(grep "MemTotal" /proc/meminfo)"
echo "    $(grep "MemFree" /proc/meminfo)"
