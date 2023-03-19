# author:	 Au Doan Ngoc (doanngocau99@gmail.com)
# version:	 0.1
# date:		 2023-03-18

# Copyright (c) 2023

CC = g++
CFLAGS = -g -Wall -Wextra -pthread
INC	+= -I./src
SRC += ./src/*.cpp
OUT = server.out

.PHONY:	build run clean

build:
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(OUT)
run:
	./$(OUT)
clean:
	rm $(OUT)