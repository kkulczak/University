#include <cstdio>
#include <algorithm>

int K[1005][105];
int cost[105];
int weight[105];
int w,N;

void print_data()
{
  puts("items:");
  for(int i=0; i<N; i++)
  {
    printf("cost:%d weight:%d\n",cost[i], weight[i] );
  }
  puts("K:");
  for(int i=0; i<w; i++)
  {
    for(int j= 0; j<N; j++)
    {
      printf("%2d ",K[i][j] );
    }
    puts("");
  }
}

int main()
{
  scanf("%d\n",&N );
  for(int i=0; i<N; i++)
  {
    scanf("%d %d\n",&weight[i+1], &cost[i+1] );
  }
  scanf("%d\n",&w );
  w++;N++;
  for(int i=0; i< N; i++)
  {
    K[0][i]=0;
  }
  for(int i =0; i<w; i++)
  {
    K[i][0] = 0;
  }
  for(int j=1; j<N; j++)
  {
    for(int i=1; i<w; i++ )
    {
      K[i][j] = std::max( K[i][j-1] ,  i-weight[j] < 0 ? 0 : cost[j] +  K[i-weight[j]][j-1]   );
    }
  }

  printf("%d\n",K[w-1][N-1] );
  // print_data();
  return 0;
}
