#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <cstring>

using namespace std;

#define SIZE 500005

vector<int> tree[SIZE];
int color[SIZE];
bool visited[SIZE];
int N;


int find_root(int vortex, int blockedVortex) {
    int firstColor = color[vortex];
    stack<int> stackD;
    stackD.push(vortex);

    while (!stackD.empty()) {
        int v = stackD.top();
        stackD.pop();

        visited[v] = 1;
        for (size_t i=0; i < tree[v].size(); i++) {
            if (visited[tree[v][i]] || blockedVortex == tree[v][i])
                continue;
            if (color[tree[v][i]] != firstColor)
                return tree[v][i];
            stackD.push(tree[v][i]);
        }
    }
    return vortex;
}

void showTab() {
    for (int i=0; i<N ; i++) {
        cout << color[i] << "   children: ";
        for (size_t j=0; j<tree[i].size(); j++) {
            cout << tree[i][j] << " ";
        }
        cout << "\n";
    }
}

void readData() {
    if ( scanf("%d", &N) == 0 ){;}

    for (int i = 0; i < N -1; ++i)
    {
        int a,b;
        if ( scanf("%d %d", &a, &b) == 0 ){;}
        tree[a-1].push_back(b-1);
        tree[b-1].push_back(a-1); 
    }
    for (int i=0; i < N; i++) {
        int t;
        if ( scanf("%d", &t) == 0 ){;}
        color[i] = t;
    }

}




int main() {
    readData();
    int leaf = 0;
    for (int i=0; i<N; i++) {
        if (tree[i].size() == 1) {
            leaf = i;
            break;
        }
    }
    for (int i=leaf+1; i<N; i++) {
        if (tree[i].size() == 1) {
            leaf = i;
            break;
        }
    }
    memset(visited, 0 , SIZE);
    int root = find_root(leaf, -1);
    memset(visited, 0 , SIZE);
    visited[root] = 1;    
    for (size_t i=0; i<tree[root].size(); i++) {
        if (find_root(tree[root][i],root) != tree[root][i] ) {
            puts("NIE");
            return 0;
        }
    }
    puts("TAK");
    // showTab();
    // cout << find_root(1) << "\n";
    return 0;
}
