#include <stdio.h>
#include <stdlib.h>

typedef struct{
	unsigned long lcm,gcd;
} result_t;

extern result_t lcm_gcd(unsigned long a,unsigned long b);

int main(int argc, char* args[]){
	long a,b;
	if(argc != 3){
		fprintf(stderr,"Zle dane wejscia, plik liczba liczba\n");
		return 1;
	}
	sscanf(args[1], "%ld", &a);
	sscanf(args[2], "%ld", &b);	
	result_t res = lcm_gcd(a,b);
	printf("lcm:%lu\tgcd:%lu\n",res.lcm,res.gcd);
	
	return 0;
}
