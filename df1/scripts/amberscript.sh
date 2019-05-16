#!/bin/sh

while [ true ]
do
	if [ ! "$(ls -A /Volumes/Users/m196348/Documents/USNA/Capstone/new/)" ]
	then
		:
	else
		for filename in /Volumes/Users/m196348/Documents/USNA/Capstone/new/*; do
			tshark -r $filename -T ek -e df1.rslogixdata -e df1.dst -e df1.src -e df1.cmd -e df1.fnc -Y "df1.fnc == 0xa3" > $filename.json
			curl -s -k -L -u kibana:ambersloth -H "Content-Type: application/x-ndjson" -XPOST "http://cyber.moboard.com/elk/_bulk" --data-binary @$filename.json
			mv $filename ./old/
			mv $filename.json ./old/
		
		done
	fi
	rm -rf /Volumes/Users/m196348/Documents/USNA/Capstone/new/*
        rm -rf ./old/*
	sleep 5
done
