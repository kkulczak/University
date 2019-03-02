#include <cstdio>
#include <iostream>
#include <cstdio>
#include <vector>

#define MAX_TOWERS 200005
#define SIZE_TREE (1048576)
#define ZERO_PLACE 524288
#include<vector>
#include<cstdio>
#include<algorithm>

size_t _cnt[SIZE_TREE * 2 + 5];
size_t _max[SIZE_TREE * 2 + 5];
size_t lastItem = SIZE_TREE * 2 - 1;
struct interval {
  size_t a;
  size_t b;
} opInterv;

size_t queryValue;
size_t insertValue;

void init(size_t a, size_t b, size_t value) {
  opInterv.a = a;
  opInterv.b = b;
  queryValue = 0;
  insertValue = value;
}

void insert(size_t k, size_t a, size_t b) {
  // std::cout << k <<  " a:"<< a << " b:" << b <<"\n";
  // getchar();
  if ((a >= opInterv.a && b <= opInterv.b)) {
   _cnt[k] = std::max(insertValue, _cnt[k]);
   _max[k] = std::max(insertValue, _max[k]);
   return;
  }
  int m = (a+b)/2;
  if ( opInterv.a <= m )
    insert(  2*k,   a, m);
  if ( opInterv.b > m  )
    insert(2*k+1, m+1, b);
  _max[k] = std::max(std::max( _max[2*k], _max[2*k+1] ), _cnt[k]);
}

void query(size_t k, size_t a, size_t b) {
  if ((a >= opInterv.a && b <= opInterv.b)) {
   queryValue = std::max(queryValue, _max[k]);
   // std::cout << k <<  " a:"<< a << " b:" << b <<"\n";
   return;
  }
  int m = (a+b)/2;
  if ( opInterv.a <= m )
    query(  2*k,   a, m);
  if ( opInterv.b > m  )
    query(2*k+1, m+1, b);
  queryValue = std::max(queryValue, _cnt[k]);
  // std::cout << k <<  " a:"<< a << " b:" << b <<"\n";
}


void showLine(size_t start, size_t howMany) {
  for (size_t i = 0; i < howMany; ++i)
  {
    std::cout << "(" <<_cnt[start+i] << "," <<_max[start+i] << ")";
  }
  std::cout << "\n";
}

void showTree() {
    std::cout << "START TREE\n";
    size_t howMany = 1;
    for (size_t i=SIZE_TREE / 16; i <= SIZE_TREE; i*=2) {
      showLine(i,howMany);
      // std::cout << i << "," << howMany << "\n";
      howMany *= 2;
    }
    std::cout << "END TREE\n\n";
  }

  void showWhat() {
    for (int i = 0; i < lastItem; ++i)
    {
      if(_cnt[i]) {
        std::cout << i<<": (" <<_cnt[i] << "," <<_max[i] << ")\n";
      }
    }
  }

size_t * starting, * ending,* tab;
size_t n;
std::pair<size_t,size_t> data[MAX_TOWERS];
// struct node  tree[SIZE_TREE *2 +10];


void treeInsert(size_t a, size_t b, size_t value) {
  init(a,b,value);
  insert(1,0,SIZE_TREE-1);
}

size_t treeQuery(size_t a, size_t b) {
  init(a,b,0);
  query(1,0,SIZE_TREE-1);
  return queryValue;
}

void read_data();

int main()
{
  read_data();
  // erase_data();
  for(size_t i=0; i<n; i++)
    {
      size_t start = data[i].second;
      size_t end = data[i].first + data[i].second - 1;
      // std::cout << "<" << start << "," << end << ">\n";

      size_t newSize = treeQuery(start, end) + 1;

      // std::cout << newSize << "\n";
      treeInsert(start, end, newSize);
      // tree.showLine(SIZE_TREE, 10);
      // showTree();
    }
    // treeInsert(1,3,1);
    // showTree();
    std::cout << _max[1] << "\n";

  return 0;
}

void read_data() {
  int temp;
  scanf("%d %zu", &temp ,&n);
  for(size_t i=0; i<n; i++) {
    size_t a,b;
    scanf("%zu %zu", &a, &b);
    data[i] = std::make_pair(a,b);
    // std::cout << "<" << data[i].first << "," << data[i].second << ">\n";
  }
  // std::cout << "End of data..........\n";
}

