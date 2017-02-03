Flags = -Og -Wall -Wextra

main: main.o insertsort.o
	gcc $(Flags) -o main main.o insertsort.o
insertsort.o: insertsort.s
	gcc  -c $(Flags) -Og -Wall -Wextra insertsort.s -o insertsort.o
main.o: main.c
	gcc -c $(Flags) main.c -o main.o
clean:
	rm -f main.o insertsort.o main
