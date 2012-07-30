#!/system/bin/sh

while [ 1 ];
do
	sleep 10800 
	busybox killall rild
	log -p i "Restart rild done"
done
