#include <iostream>
#include <cstdio>
#include <cstdlib>

#define SIZE 100005
#define TREE_SIZE 262144
#define M 131072

int tab[SIZE];
size_t N,K;
int w[TREE_SIZE];

void insert(int x, int val) {
   int v = M + x;
   w[v] = val;
   while (v != 1) {
     v /= 2;
     w[v] = w[2 * v] * w[2 * v + 1];
   }
}

int query(int a, int b) {
   int va = M + a, vb = M + b;
   int wyn = w[va];
   if (va != vb) wyn *= w[vb];
   while (va / 2 != vb / 2) {
     if (va % 2 == 0) wyn *= w[va + 1]; 
     if (vb % 2 == 1) wyn *= w[vb - 1]; 
     va /= 2; vb /= 2;
   }
   return wyn;
}

void showTab() {
    for(size_t i=1; i<=N; i++) {
        int t = tab[i];
        std::cout << (t > 0 ? '+' : (t < 0 ? '-' : '0'));
    }
    std::cout << "\n";
}

void readData() {
    for (int i=0; i < TREE_SIZE; i++)
        w[i] = 1;
    if ( scanf("%zu %zu", &N, &K) == EOF )
        exit(0);
    for (size_t i = 1; i <= N; ++i)
    {
        int t;
        if ( scanf("%d", &t) == EOF )
            exit(0);
        insert(i ,t > 0 ? 1 : (t < 0 ? -1 : 0));
    }
}

void executeRound() {
    char Type;
    size_t index;
    int value;
    size_t start,end;
    if ( scanf("%s", &Type) == EOF )
        exit(0);
    // std::cout << "\nType:" << Type << "\n\n";
    if (Type == 'C') {
        if ( scanf("%zu %d",&index, &value) == EOF )
            exit(0);
        insert(index, value > 0 ? 1 : (value < 0 ? -1 : 0));
    // showTab();

    }
    else if (Type == 'P') {
        if (scanf("%zu %zu", &start, &end) == EOF)
            exit(0);
        size_t res=1;
        res = query(start, end);
        switch (res) {
            case 1:
                putchar('+');
                break;
            case -1:
                putchar('-');
                break;
            case 0:
                putchar('0');
                break;
        }
    }
    else {
        exit(0);
    }
}


int main() {
    while(1) {
        readData();
        for(size_t i=0; i<K; i++) {
            // std::cout << "what? "<< i << "\n";
            executeRound();
        }
        putchar('\n');
    }
}
