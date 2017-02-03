#include <stdio.h>
#include <stdlib.h>



int main(int argc, char* args[]){
	long a,b,c;
	if(argc != 3){
		fprintf(stderr,"Zle dane wejscia, plik liczba liczba\n");
		return 1;
	}
	sscanf(args[1], "%ld", &a);
	sscanf(args[2], "%ld", &b);
	asm(
		"add	%0,	%1;"
		"mov	$-1,	%2;"
		"adox	$0,	%2;"
		"and	%2,	%1;"
		"negg	%2;"
		"shr	$63,	%0;"
		"add	$0x7FFFFFFF,	%0;"
		"and	%2,	%0;"
		"leaq	(%0,%1),	%2;"
		: "+r" (a), "+r" (b)
		: "-r" (c)
		);
	
	printf("%ld\n", c );
	
	return 0;
}
