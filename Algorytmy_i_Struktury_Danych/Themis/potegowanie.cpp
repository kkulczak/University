#include <iostream>
#include <stdio.h>

typedef long long int matrix[2][2];
static long long int m;

void init(matrix a)
{
  for(int i=0; i<2;i++)
  {
    for( int j=0; j<2; j++)
    {
      a[i][j]=0;
    }
  }
}

void mult(const matrix & a, matrix & b)
{
  matrix temp;
  init(temp);
  for(int i=0; i<2; i++)
  {
    for(int j=0; j<2; j++)
    {
      for(int k=0; k<2;k++)
      {
        temp[i][j] =  ((((a[i][k] * b[k][j]) % m) ) + temp[i][j] ) % m;
      }
    }
  }
  for(int i=0; i<2; i++)
  {
    for(int j=0; j<2; j++)
    {
      b[i][j] = temp[i][j];
    }
  }
}

void pow(matrix & a,long long int n)
{
  if(n == 1) return;
  if(n % 2 == 1)
  {
    matrix t;
    for(int i=0; i<2; i++)
    {
      for(int j=0; j<2; j++)
      {
        t[i][j] = a[i][j];
      }
    }
    pow(a,n-1);
    mult(t,a);
    return;
  }
  pow(a,n/2);
  mult(a,a);
  return;
}

void show(const matrix & a)
{
  for(int i=0; i<2; i++)
  {
    for(int j=0; j<2; j++)
    {
      std::cout << a[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main()
{

  int T;
  scanf("%d",&T);
  for(int i=0; i<T; i++)
  {
    long long int n;
    scanf("%lld %lld",&n ,&m);
    if(n==1)
    {
      printf("%d\n",1);
      continue;
    }
    matrix t = {{1,1},{1,0}};
    pow(t,n-1);
    printf("%lld\n",t[0][0] );
  }

/*
long long int pown;
std::cin >> pown;
matrix t = {{1,1},{1,0}};
pow(t,pown-1);
printf("%lld\n",t[0][0] );
*/
  return 0;
}
