#!/bin/bash

pid=$(pgrep -f q1Script.sh)

echo "Process information: "
ps -p "$pid" -o pid,%cpu,%mem,cmd

kill -9 "$pid"
if [ $? -eq 0 ]; then
	echo "Disruptive process has been killed successfully."
fi
