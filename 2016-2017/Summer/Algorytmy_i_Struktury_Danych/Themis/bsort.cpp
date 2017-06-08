#include <cstdio>
#include <iostream>
#include <vector>

std::vector<int> tab;
static int n,m;

int bsearch(int target)
{
  int fst = 0;
  int lst = n+1;
  while(fst != lst -1)
  {
    int mid = (lst+fst)/2;
    if(tab[mid] < target)
    {
      fst = mid;
    }
    else
    {
      lst = mid;
    }
  }
  return lst;
}

//void show()
//{
//  for(int i=0; i<n; i++)
//  std::cout << tab[i] << "\n";
//  std::cout << "\n";
//}

int main()
{
  /*
  n=8;
  my dane[8] = {1, 10 ,12, 20, 30, 40 , 45, 50};
  for(int i=0; i<n; i++ )
  {
    tab[i]=dane[i];
  }

  std::cout << bsearch(1) << "\n";

*/
  scanf("%d",&n);
  tab.resize(n+2);
  tab[0] = -1;
  tab[n+1] = 1000005;
  for(int i=1; i<=n; i++)
  {
    scanf("%d\n", &tab[i] );
  }
  scanf("%d",&m);
  for(int i=0; i<m; i++)
  {
    int num;
    scanf("%d",&num);
    printf("%d ",n - bsearch(num) +1 );
  }

  return 0;
}
