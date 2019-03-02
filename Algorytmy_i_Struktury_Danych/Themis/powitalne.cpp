//Kacper Kulczak
//279079
//LJe Lukasz Jeż
#include <stdio.h>
int main()
{	
	int a,b;
	scanf("%d %d",&a,&b);
	if(a % 2 == 0) a++;
	if(b % 2 == 0) b--;
	for(int i=a; i<=b; i = i+2)
	{
		printf("%d ",i);
	}
	
	return 0;
}


