#include <stdio.h>
#include <iostream>

static long int md;

class vector
{	
	public:

	long int x;
	long int y;
	
	
	vector(int a, int b)
	{x=a,y=b;}
	
	long int fst()
	{
		return x;
	}
};


class matrix
{	
	public:
	long int repr[2][2];
	
	public:
	matrix()
	{
		for(int i=0; i<2; i++)
	{
		for(int j=0; j<2;j++)
		{
			repr[i][j]=0;
		} 
	}
	}
	matrix(int a, int b, int c ,int d)
	{
		repr[0][0] = a;
		repr[0][1] =b;
		repr[1][0] = c;
		repr[1][1] = d;
	}

}; 

vector operator * (const matrix & m,const vector & v)
{
	return vector( v.x * m.repr[0][0] + v.y * m.repr[0][1], v.x * m.repr[1][0] + v.y * m.repr[1][1] );
}

matrix operator * (const matrix & m1, const matrix & m2)
{
	matrix result = matrix();
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2;j++)
		{
			for(int k= 0; k<2; k++)
			{
				result.repr[i][j] += (m1.repr[i][k] * m2.repr[k][j]) % md;
			}
		} 
	}
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<2;j++)
		{
		
			result.repr[i][j] %=  md;
		}
	} 
	
	return result;
}

void show(const matrix & m)
{
for(int i=0; i<2; i++)
	{
		for(int j=0; j<2;j++)
		{
			std::cout << m.repr[i][j] << " ";
		} 
		std::cout << "\n";
	}
	std::cout << "\n";
}

matrix pow(const matrix & m, long int p)
{	
	if(p == 1) return m;
	if(p%2 == 1) return m * pow(m,p-1);
	matrix temp = pow(m,p/2);
	return temp*temp;
}

int main()
{	
	int T;
	scanf("%d",&T);
	for(int i=0; i<T; i++)
	{	
		long int n;
		scanf("%ld %ld",&n,&md);
		if(n<=2) {printf("%ld\n", 1 %md); continue;}
		matrix temp = matrix(1,1,1,0);
		temp = pow(temp,n-1);
		//show(temp);
		printf("%ld\n",  temp.repr[0][0] );
	}
	

	
	return 0;
}


