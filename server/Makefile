# @author Jesutofunmi Kupoluyi
# @brief Makefile for the aesdsocket.c source file
# @date: 19 June, 2023

TARGET = aesdsocket
CROSS_COMPILE=aarch64-none-linux-gnu-
STATIC=-static
all:
	$(CROSS_COMPILE)gcc $(STATIC) $(TARGET).c -o $(TARGET)

default: all

clean:
	rm $(TARGET)
