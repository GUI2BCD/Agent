#!/bin/bash
if [ "$(whoami)" == "root" ]; then
		su $1 -c "mplayer -vo png -frames 1 tv:// 2> /dev/null > /dev/null"
else
		mplayer -vo png -frames 1 tv:// 2> /dev/null > /dev/null
fi

echo $?
