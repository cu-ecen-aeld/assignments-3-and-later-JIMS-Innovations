/*
* @file: writer.c
*
* @author: Jesutofunmi Kupoluyi (jimsufficiency@gmail.com)
* 
* @brief: This is a program for writing strings to files.
*
* @date: 12 March, 2023
*
*/

/* Including necessary libraries*/
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

	if(argc < 2){
		FILE *fp;
		fp = fopen(argv[1], "w");
		fprintf(fp, "%s\n", argv[2]);
		syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
		printf("Writing %s to %s\n", argv[2], argv[1]);
		int cl_stat = fclose(fp);
		!cl_stat ? syslog(LOG_DEBUG, "File close successful!") : syslog(LOG_DEBUG, "File close fail!"); 
	}
	else{
		syslog(LOG_ERR, "Not enough arguments!");
		printf("Not enough arguments!\n");
		return 1;
	}

	closelog();	

	return 0;
}
