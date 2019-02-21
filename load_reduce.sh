#! /bin/bash

ps aux --sort -%cpu | tail -n +2 > info
echo "There are $(wc -l info) proccesses running "
echo "There are $(awk '{print $1}' info| sort | uniq | wc -l) users with proccesses running"
head -n +1 info > info2 # Only need the first line for last 2 parts
rm info # Don't need the info file anymore
echo "The busiest process is $(awk '{print $11, $12}' info2) and is being run by $(awk '{print $1}' info2)"
if [[ "$(awk '{print $3}' info2)" =~ [6-9][0-9]\.[0-9] ]];
then
	kill_pid=$(awk '{print $2}' info2)
	echo "Proccess PID: $kill_pid, using more than 60%, killing..."
	kill $kill_pid
	echo "Proccess killed"
fi
rm info2
