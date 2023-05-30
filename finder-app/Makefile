# Author: Jesutofunmi Kupoluyi
# Brief: this is a makefile for building the writer.c 
# source file.
# Date: 9 May, 2023

default:
	$(CROSS_COMPILE)gcc writer.c -o writer
all:
	$(CROSS_COMPILE)gcc writer.c -o writer

CROSS_COMPILE:
	aarch64-none-linux-gnu-gcc writer.c -o writer
	
clean:
	rm -rf *.o writer
 
