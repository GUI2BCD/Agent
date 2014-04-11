#!/bin/bash
if [ "$(whoami)" == "root" ]; then
                iwlist scan 2>/dev/null | grep 'ESSID' | awk -F':' '{ print $2 }'
else
                echo 'Could not collect wifi hotspots. Not root.'
fi


