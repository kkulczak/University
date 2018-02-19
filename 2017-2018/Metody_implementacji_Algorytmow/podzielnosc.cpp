//COs jest nie teges  ztym

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <queue>
#include <cstring>

typedef long long int my_t;  

#define SIZE 1000005


my_t N;
my_t from[SIZE];
char withNum[SIZE];
char ansewer[SIZE];
std::queue<my_t> q;



void genRes() {
    my_t actRes = 0, i=0;
    for (;actRes >= 0; actRes = from[actRes]) {
        ansewer[i++] = withNum[actRes];
    }
    for (my_t j=0; j < i; j++) {
        printf("%d", ansewer[i-j - 1]);
    }
    puts("");
    exit(0);
}

void logNumber(my_t obj, my_t num) {
    my_t nextObj = (obj * 10 + num) % N;
    if (withNum[nextObj] != -1) {
        return;
    }
    from[nextObj] = obj;
    withNum[nextObj] = num;
    if (nextObj == 0) {
        genRes();
    }
    // std::cout << "pushed: " << nextObj << "\n";
    q.push(nextObj);
}


int main() {
    memset(ansewer, -1, sizeof(ansewer));    
    memset(from, -1, sizeof(from));
    memset(withNum, -1, sizeof(withNum));
    if ( scanf("%lld", &N)) {;}
    q.push(1);
    withNum[1] =1;

    while (!q.empty()) {
        my_t obj = q.front();
        q.pop();
        logNumber(obj, 0);
        logNumber(obj, 1);
    }

    return 0;
}
