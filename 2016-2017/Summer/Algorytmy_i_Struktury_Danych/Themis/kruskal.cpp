#include <cstdio>
#include <algorithm>


int tab[7005], ile[7005];
std::pair <std::pair<int,int>, std::pair <int, int> > edges[300005];
int n,m;

bool compare( const std::pair <std::pair<int,int>, std::pair <int, int> > &i,
                const std::pair <std::pair<int,int>, std::pair <int, int> > &j)
{
    if(i.first.first == j.first.first)
    {
      return i.first.second < j.first.second;
    }
    else
    {
      return i.first.first < j.first.first;
    }
}


void showtest()
{
  for(int i=0; i<m; i++)
  {
    printf("c:%d m:%d %d %d\n",edges[i].first.first, edges[i].first.second, edges[i].second.first, edges[i].second.second );
  }
}

int Find(int a)
{
  return (tab[a] == a ? a : tab[a] = Find(tab[a]) );
}

bool Union(int a, int b)
{
  int fa = Find(a);
  int fb = Find(b);
  if(fa == fb) return false;
  else
  {
    if( ile[fa] <= ile[fb] )
    {
      ile[fb] += ile[fa];
      tab[fa] = fb;
    }
    else
    {
      ile[fa] += ile[fb];
      tab[fb] = fa;
    }
  }
  return true;
}

int main()
{
  scanf("%d %d\n",&n,&m );
  for(int i=0; i < m; i++)
  {
    //edges[i].first.second = i+1;
    int a ,b ,c;
    scanf("%d %d %d\n",&a, &b, &c);
    edges[i] = std::make_pair(std::make_pair(c,i+1),std::make_pair(a,b));
  }
  for(int i=1; i<1+n; i++)
  {
    tab[i]=i;
    ile[i]=1;
  }
  std::sort(edges, edges+m, compare);
  int cost=0;
  for(int i=0; i<m; i++)
  {
    if(Union(edges[i].second.first, edges[i].second.second))
    {
      cost += edges[i].first.first;
    }
  }
  printf("%d\n",cost );

  return 0;
}
