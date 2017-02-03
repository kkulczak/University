Flags = -Og -Wall -Wextra

main: main.o lcm_gcd.o
	gcc $(Flags) -o main main.o lcm_gcd.o
lcm_gcd.o: lcm_gcd.s
	gcc  -c $(Flags) -Og -Wall -Wextra lcm_gcd.s -o lcm_gcd.o
main.o: main.c
	gcc -c $(Flags) main.c -o main.o
clean:
	rm -f main.o lcm_gcd.o main
