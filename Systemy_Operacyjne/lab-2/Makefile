CFLAGS = -std=gnu99 -Wall -Wextra -Wshadow -pthread
LDFLAGS = -pthread -lrt
CC = gcc

all: zad3 zad4 semaphore_test zad2a zad2b clearSem

semaphore_test: semaphore.o
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ semaphore.o semaphore_test.c $(LDFLAGS) 

semaphore.o:

clearSem:

zad3: zad3.c
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ zad3.c $(LDFLAGS) 

zad4:

zad2a: semaphore.o zad2a.c
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ semaphore.o zad2a.c $(LDFLAGS) 

zad2b: zad2b.c
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ zad2b.c $(LDFLAGS) 

debug: CXXFLAGS += -DDEBUG -g
debug : all

clean:
	$(RM) *.o main zad1 zad2a zad2b zad3 zad4 zad5 zad6 semaphore_test clearSem
