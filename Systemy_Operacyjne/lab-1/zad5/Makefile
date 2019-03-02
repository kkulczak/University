DIR = $(strip $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
CXXFLAGS = -std=gnu99 -Wall -Wextra -Wshadow
CXX = gcc
LINK = -L$(DIR) -lshared
E5OPTS = $(OPTS) $(LINK) -Wl,-rpath=$(DIR) 


all: main mainDL libshared.so

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o -lshared -L. -Wl,-rpath,.

main.o: main.c ../utils.h myStr.h
	$(CXX) -c $(CXXFLAGS) -o main.o main.c

mainDL: mainDL.o 
	$(CXX) $(CXXFLAGS) -o mainDL mainDL.o -ldl 

mainDL.o: mainDL.c ../utils.h myStr.h
	$(CXX) -c $(CXXFLAGS) -o mainDL.o mainDL.c

myStr.o : myStr.c myStr.h
	$(CXX) -c $(CXXFLAGS) -fPIC -o myStr.o myStr.c

libshared.so :myStr.o 	
	$(CXX) -shared -o libshared.so myStr.o

debug: CXXFLAGS += -DDEBUG -g
debug : all

clean:
	$(RM) *.o main mainDL *.so
