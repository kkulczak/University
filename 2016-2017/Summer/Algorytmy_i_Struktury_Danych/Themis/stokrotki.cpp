#include <cstdio>
#include <algorithm>
#include <iostream>

int data[1005][1005];
int answer[1005][1005];
int n,m;

int main()
{
  int times=1;
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
      for(int i=0; i<n; i++)
      {
        int my_min= answer[i][j-1];
        if(i > 0)
        {
          my_min= std::min(my_min,answer[i-1][j-1]);
        }
        if(i < n-1)
        {
          my_min = std::min(my_min, answer[i+1][j-1]);
        }
        answer[i][j] = data[i][j]+my_min;
      }
    }

    //find min
    int ret_val = answer[0][m-1];
    for(int i=1; i<n; i++)
    {
      ret_val = std::min(answer[i][m-1],ret_val);
    }
    std::cout << ret_val<< '\n';

  }
  return 0;
}
