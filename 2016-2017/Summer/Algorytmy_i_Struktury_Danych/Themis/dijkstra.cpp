#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

#define MAX_N 7010
#define MAX_D 9223372036854775805

static long int n,m;
// <waga, wierzch>
static std::vector<std::pair<long int,long int>  > edges[MAX_N];

static long long int distance[MAX_N];

void init();
void dijkstra();

int main()
{
  init();
  if ( !scanf("%ld %ld",&n, &m) ) return 1;
  for(int i=0; i<m; i++)
  {
    long int a,b,c;
    if ( !scanf("%ld %ld %ld",&a,&b,&c) ) return 1;
    edges[a].push_back(std::make_pair(c,b));
    edges[b].push_back(std::make_pair(c,a));
  }
  dijkstra();
  for(int i=2; i<=n; i++)
  {
    printf("%lld ",distance[i]);
  }


  return 0;
}

void dijkstra()
{
  std::priority_queue<std::pair <long int, long int> > layer;
  layer.push(std::make_pair(0,1));
  while( !layer.empty() )
  {
    long int v = layer.top().second;
    layer.pop();
    for(int i=0; i < edges[v].size(); i++)
    {
      if( distance[edges[v][i].second] > distance[v] + edges[v][i].first )
      {
        distance[edges[v][i].second] = distance[v] + edges[v][i].first;
        layer.push( std::make_pair( -distance[edges[v][i].second], edges[v][i].second ));
      }
      else
      {

      }
    }
  }
}



void init()
{
  for(int i=0; i<MAX_N; i++)
  {
    distance[i] = MAX_D;
  }
  distance[1] = 0;
}
