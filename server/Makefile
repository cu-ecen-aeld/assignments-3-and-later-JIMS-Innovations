# @author Jesutofunmi Kupoluyi
# @brief Makefile for the aesdsocket.c source file
# @date: 19 June, 2023

TARGET = aesdsocket
CC = gcc

CFLAGS = -static -g -Wall -Werror

.PHONY: all
all:
	$(CROSS_COMPILE) $(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

default: all

.PHONY: clean
clean:
	rm $(TARGET)
