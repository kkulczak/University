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
#include <stack>


typedef long long int my_t;  

#define MAX_ENVELOPS 1000005

int envelops[MAX_ENVELOPS];
my_t T,N,S,X;



void init() {
    memset(envelops, 0, sizeof(envelops));
    // memset(visited, 0, sizeof(visited));
    // for (my_t i=0; i < M; i++) {
    //     change(data[i][0], data[i][1]);
    // }
}

void runAlgorithm() {
    init();
    std::priority_queue<my_t, std::vector<my_t> ,std::greater<my_t> > queue;
    std::stack<my_t> stack;

    for (int i = 0; i < N; ++i)
    {
        if ( scanf("%lld", &X)) {;}
        if (X > 0) {
            queue.push(X);
            stack.push(X);
            // envelops[X]++;
        }
        if (X < 0) {
            my_t toPay = X;
            if (stack.empty() || -toPay < queue.top()) {
                S += toPay;
            } else {
                while (toPay < 0 && !stack.empty()) {
                    toPay += stack.top();
                    envelops[stack.top()]++;
                    stack.pop();
                }
                S += toPay;
                while(!queue.empty() && envelops[queue.top()] > 0) {
                    envelops[queue.top()]--;
                    queue.pop();
                }
            }
        }
    }
    my_t inEnvelops = 0;
    while (!stack.empty()) {
        inEnvelops += stack.top();
        stack.pop();
    }
    printf("%lld %lld\n",S, inEnvelops);
}




int main() {
    if ( scanf("%lld", &T)) {;}
    for (int i=0 ; i < T; i++) {
        if ( scanf("%lld %lld", &N, &S)) {;}
        runAlgorithm();        
    }    
    return 0;
}
