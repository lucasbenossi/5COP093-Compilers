#!/bin/bash

for FILE in $@
do
	if [[ -f $FILE ]]
	then
		rm $FILE
	fi
done
