#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <cstring>
#include <queue>


typedef int my_t;  

#define MAX_TOWNS 1005
my_t N,M;
my_t data[(MAX_TOWNS) * (MAX_TOWNS - 1) / 2][2];
my_t tab[MAX_TOWNS][MAX_TOWNS];
bool visited[MAX_TOWNS];

void change(my_t i, my_t j) {
    if (i > j) {
        std::swap(i,j);
    }
    tab[i][j]++;
}

bool exists(my_t i, my_t j) {
    if (i > j) {
        std::swap(i,j);
    }
    return tab[i][j] % 2 == 1;
}

void revertVortex(my_t v) {
    for (my_t i=0; i < N; i++) {
        if (i == v)
            continue;
        change(v, i);
    }
}

void init() {
    memset(tab, 0, sizeof(tab));
    memset(visited, 0, sizeof(visited));
    for (my_t i=0; i < M; i++) {
        change(data[i][0], data[i][1]);
    }
}

void readData() {
    if ( scanf("%d", &N)) {;}
    if ( scanf("%d", &M)) {;}
    
    for (int i = 0; i < M; ++i)
    {
        if ( scanf("%d %d", &data[i][0], &data[i][1])) {;}
        for (int j=0; j < 2; j++) {
            data[i][j]--;
        }
    }
}

bool isOk() {
    for (int i=0; i< N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j)
                continue;
            if (!exists(i,j)) {
                return false;
            }
        }
    }
    return true;
}

bool bfs() {
    std::queue<my_t> q;
    visited[0] = true;
    q.push(0);
    while (!q.empty()) {
        my_t v = q.front();
        q.pop();

        for (my_t i=0; i < N; i++) {
            if (v == i)
                continue;
            if (!exists(v, i) && !visited[i]) {
                visited[i] = true;
                q.push(i);
                revertVortex(i);
            }
        }
    }
    if (isOk()) {
        return true;
    }
    return false;
}


int main() {
    readData();
    for (int i=0; i<2; i++) {
        init();
        if (i == 1) {
            revertVortex(0);
        }
        if (bfs()) {
            puts("DA");
            return 0;
        }
    }
    puts("NE");
    return 0;
}
