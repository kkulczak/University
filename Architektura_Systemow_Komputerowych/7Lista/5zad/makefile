Flags = -Og -Wall -Wextra -g

main: main.o mulf.o
	gcc $(Flags) -o main main.o mulf.o
mulf.o: mulf.s
	gcc  -c $(Flags) mulf.s -o mulf.o
main.o: main.c
	gcc -c $(Flags) main.c -o main.o
clean:
	rm -f main.o mulf.o main
