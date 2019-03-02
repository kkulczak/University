#include <cstdio>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int data[1005][1005];
int answer[1005][1005];
int prev[1005][1005];
int n,m;
int route[1005];

void print_best(int i,int j)
{
  if( j != 0)
  {
    print_best(prev[i][j], j-1);
  }
  printf("%d ",i);
}

int main()
{
  int times = 1;
  // std::cin >> times;
  for(int t=0; t<times; t++)
  {
    std::cin >> n >> m;
    for(int i=0; i<n; i++)
    {
      for(int j=0; j<m; j++)
      {
        std::cin >> data[i][j];
      }
    }

    for(int i=0; i<n ;i++)
    {
      answer[i][0] = data[i][0];
    }

    for(int j=1; j<m ;j++)
    {
      if( answer[0][j-1] < answer[1][j-1])
      {
        answer[0][j] = data[0][j] + answer[0][j-1];
        prev[0][j] = 0;
      }
      else
      {
        answer[0][j] = data[0][j] + answer[1][j-1];
        prev[0][j] = 1;
      }
      for(int i=1; i<n-1; i++)
      {
        if(answer[i-1][j-1] < answer[i][j-1])
        {
          if(answer[i-1][j-1] < answer[i+1][j-1])
          {
            answer[i][j] = data[i][j]+answer[i-1][j-1];
            prev[i][j] = i-1;
          }
          else
          {
            answer[i][j] = data[i][j]+answer[i+1][j-1];
            prev[i][j] = i+1;
          }
        }
        else
        {
          if(answer[i][j-1] < answer[i+1][j-1])
          {
            answer[i][j] = data[i][j]+answer[i][j-1];
            prev[i][j] = i;
          }
          else
          {
            answer[i][j] = data[i][j]+answer[i+1][j-1];
            prev[i][j] = i+1;
          }
        }
        // int my_min= answer[i][j-1];
        // if(i > 0)
        // {
        //   my_min= std::min(my_min,answer[i-1][j-1]);
        // }
        // if(i < n-1)
        // {
        //   my_min = std::min(my_min, answer[i+1][j-1]);
        // }
        // answer[i][j] = data[i][j]+my_min;
      }
      if( answer[n-1][j-1] < answer[n-2][j-1])
      {
        answer[n-1][j] = data[n-1][j] + answer[n-1][j-1];
        prev[n-1][j] = n-1;
      }
      else
      {
        answer[n-1][j] = data[n-1][j] + answer[n-2][j-1];
        prev[n-1][j] = n-2;
      }
    }

    //find min
    int ret_val = answer[0][m-1];
    int index = 0;
    for(int i=1; i<n; i++)
    {
      if(answer[i][m-1] < ret_val)
      {
        ret_val = answer[i][m-1];
        index = i;
      }
    }
    print_best(index, m-1);
  }

  // puts("");puts("");
  // for(int i=0; i<n; i++)
  // {
  //   for(int j=0; j<m; j++)
  //   {
  //     printf("%d ",data[i][j]);
  //   }
  //   puts("");
  // }puts("");puts("");
  // for(int i=0; i<n; i++)
  // {
  //   for(int j=0; j<m; j++)
  //   {
  //     printf("%d ",answer[i][j]);
  //   }
  //   puts("");
  // }puts("");puts("");
  // for(int i=0; i<n; i++)
  // {
  //   for(int j=0; j<m; j++)
  //   {
  //     printf("%d ",prev[i][j]);
  //   }
  //   puts("");
  // }puts("");puts("");
  return 0;
}
