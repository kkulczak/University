#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

#define SIZE 100005
#define TREE_SIZE 262144
#define M 131072

struct cow {
    vector<int> children; 
    int proficiency;
    int result;
};

int toSort[SIZE];

struct cow cows[SIZE];

int tab[SIZE];
int N,K;
int tree[TREE_SIZE];


void insert(int x, int val) {
   int v = M + x;
   tree[v] = val;
   while (v != 1) {
     v /= 2;
     tree[v] = tree[2 * v] + tree[2 * v + 1];
   }
}

int query(int a, int b) {
   int va = M + a, vb = M + b;
   int wyn = tree[va];
   if (va != vb) wyn += tree[vb];
   while (va / 2 != vb / 2) {
     if (va % 2 == 0) wyn += tree[va + 1]; 
     if (vb % 2 == 1) wyn += tree[vb - 1]; 
     va /= 2; vb /= 2;
   }
   return wyn;
}

void showTab() {
    for (int i=0; i<N ; i++) {
        cout << cows[i].proficiency << "   children: ";
        for (size_t j=0; j<cows[i].children.size(); j++) {
            cout << cows[i].children[j] << " ";
        }
        cout << "\n";
    }
}

void readData() {
    for (int i=0; i < TREE_SIZE; i++)
        tree[i] = 0;
    if ( scanf("%d", &N) == 0 ){;}

    for (int i = 0; i < N; ++i)
    {
        int t;
        if ( scanf("%d", &t) == 0 ){;}
        cows[i].proficiency = t;
    }
    for (int i=1; i < N; i++) {
        int t;
        if ( scanf("%d", &t) == 0 ){;}
        cows[t-1].children.push_back(i);
    }

}

int sortFun (const void * a, const void * b)
{
  if ( cows[*(int*)a].proficiency <  cows[*(int*)b].proficiency ) return -1;
  if ( cows[*(int*)a].proficiency == cows[*(int*)b].proficiency ) return 0;
  return 1;
}

void reduceNums() {
    for (int i=0; i<N; i++) {
        toSort[i] = i;
    }
    qsort(toSort, N, sizeof(int), sortFun);
    for (int i=0; i < N; i++) {
        cows[toSort[i]].proficiency = i+1;
    }
}

void run(int i, int previus) {
    for (size_t j=0; j < cows[i].children.size(); j++) {
        int t = query(cows[cows[i].children[j]].proficiency + 1, N+2);
        run(cows[i].children[j], t);
    }
    insert(cows[i].proficiency, 1);
    cows[i].result = query(cows[i].proficiency + 1, N +2) - previus;
}




int main() {
    readData();
    reduceNums();
    // showTab();
    run(0, 0);

    for(int i=0; i<N; i++) {
        printf("%d\n", cows[i].result);
    }
    return 0;
}
