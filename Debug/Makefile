#!/bin/makefile

OFILES=main.o 
OFILESDEST=main.o ../pyList.hpp
EXEC=pyTest

LDFLAGS=-std=c++14
CFLAGS=-Wall -Wextra -std=c++14

CC=g++

CLEAN=*.o *~

all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $(OFILESDEST) -o $@ $(LDFLAGS)

%.o:%.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(CLEAN)
clear: clean

cleaner:
	rm $(EXEC) $(CLEAN)
