#!/bin/bash

#----------------------------------------------------------------
# Author: Jesutofunmi Kupoluyi
# Date: 8 March, 2023
# Brief: This is a simple shell script to write strings to a file.
#
#-----------------------------------------------------------------

NUM_OF_ARG=$#

if [ $NUM_OF_ARG -lt 2 ]
then
	echo "Error: the number of arguments is less than 2"
	exit 1
fi


WRITE_FILE=$1
WRITE_STR=$2
FILE_PATH=`dirname $WRITE_FILE`

if [ ! -d $FILE_PATH ]
then
	mkdir -p  $FILE_PATH
fi

touch $WRITE_FILE
echo $WRITE_STR > $WRITE_FILE
