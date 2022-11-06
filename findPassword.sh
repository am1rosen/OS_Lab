#!/bin/bash

while read line; do
	for password in $line; do
		unzip -P $password assignment.zip
		if [ "$?" -eq "0" ]
			then
				echo "Unzipped successfully! password: $password"
				exit 0
		fi
	done
done <"passwords.txt"

