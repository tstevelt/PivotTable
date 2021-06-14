#!/bin/sh


if [ "$1" = '' ]
then
	echo "GetFile.sh filename"
	exit
fi

FILE=$1

git restore $FILE

