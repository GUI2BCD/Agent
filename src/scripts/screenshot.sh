#!/bin/bash
if [ "$(whoami)" == "root" ]; then
                DISPLAY=:0 sudo su $1 -c "scrot screenshot.png"
else
                scrot screenshot.png
fi

echo $?
