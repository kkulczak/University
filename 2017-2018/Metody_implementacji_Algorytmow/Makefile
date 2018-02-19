# CXX = g++-4.9
CXX = g++
CXXFLAGS = -std=c++11   -lm -static -Wall -Wextra -Wshadow
# CXXFLAGS = -std=c++11 -O2 -static -lm

all: CXXFLAGS += -O2
all: main
main: main.cpp

debug: CXXFLAGS += -g -Og -DDEBUG
debug: main

clean:
	$(RM) main
