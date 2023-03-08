#!/bin/sh

#-----------------------------------------
# Author: Jesutofunmi Kupoluyi
# Date: 8 March, 2023
# Brief: This is a simple shell script for 
# finding a given string in a file
#-----------------------------------------

#Variables
NO_OF_ARG=$#

if [ $NO_OF_ARG -lt 2 ]
then
    echo "error! 2 arguments are required: [FILEDIR] [SEARCH_STR]"
    exit 1

else
    FILE_DIR=$1
    SEARCH_STR=$2
fi

if [ -d $FILE_DIR ]
then
	NO_OF_MATCHED_FILES=`grep -l $SEARCH_STR $FILE_DIR/* | wc -l`
	NO_OF_MATCHED_LINES=`grep $SEARCH_STR $FILE_DIR* -c`
	echo "The number of files are $NO_OF_MATCHED_FILES and the number of matching lines are $NO_OF_MATCHED_LINES"
else
	echo "Not a directory!"
	exit 1
fi
