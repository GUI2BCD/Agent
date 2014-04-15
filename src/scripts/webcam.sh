#!/bin/bash
if [ "$(whoami)" == "root" ]; then
		su $1 -c "streamer -t 1 -r 0.5 -o webcam.jpeg 2> /dev/null > /dev/null"
else
		streamer -t 1 -r 0.5 -o webcam.jpeg 2> /dev/null > /dev/null
fi

echo $?
