#!/bin/sh
echo "  == Wipe dir for "$1 ==
cd $1
for file in $(/sbin/busybox ls)
do
    if test -f $file
    then
        /sbin/busybox rm -rf $file
    fi
    if test -d $file
    then
        if [[ $file = "media" ]]
	then
	    echo " " $file dir is saved!
	else
	    /sbin/busybox rm -rf $file
	fi
    fi
done
exit 0
