CXXFLAGS = -std=gnu99 -Wall -Wextra -Wshadow
CXX = gcc

all: main

main: main.c ../utils.h

debug: CXXFLAGS += -DDEBUG -g
debug : all

clean:
	$(RM) *.o main
