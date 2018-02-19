
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <bitset>


typedef long long int my_t;  

#define MAXR 32
#define MAXP 15
#define MAXN 32
#define MAXM 15


#define SIZE (1 << 20)
my_t R,P,N,M;
std::bitset<MAXP> products;
my_t costs[MAXP];
std::bitset<MAXP> cookingMasks[MAXR];
my_t ansewer= 2000000000;




my_t countCost(std::bitset<MAXP>  b){
    my_t res = 0;
    for(int i=0; i < b.size(); i++) {
        if (b.test(i)) {
            res += costs[i];
        }
    }
    return res;
}

void readData() {
    if ( scanf("%lld %lld %lld %lld", &R, &P, &N, &M)) {;}
    products.reset();
    for (int i = 0; i < M; ++i)
    {
        my_t temp = 0;
        if ( scanf("%lld", &temp)) {;}
        products.set(temp, 1);
    }
    for (int i=0; i < P; i++) {
        if ( scanf("%lld", &costs[i])) {;}
    }
    for (int i=0; i < R; i++) {
        cookingMasks[i].reset();
        std::bitset<MAXP> res(0);
        for (int j=0; j< P; j++) {
            my_t temp = 0;
            if ( scanf("%lld", &temp)) {;}
            res.set(j,temp);
        }
        cookingMasks[i] = res;
    }
}

my_t howManyCanCook(std::bitset<MAXP> set) {
    my_t res=0;
    for (int i=0; i< R; i++) {
        if ((cookingMasks[i] & set) == cookingMasks[i]) {
            res++;
        }
    }
    return res;
}

void fun() {
    for (int i=1; i < (1 << P); i++) {
        std::bitset<MAXP> set(i);
        if (howManyCanCook(set) >= N) {
            set = set & (~products);
            my_t cost = countCost(set);
            ansewer = std::min(cost, ansewer);
        }
    }
}




int main() {
    int Q;
    if ( scanf("%d", &Q)) {;}
    for (int i=0; i<Q; i++) {
        ansewer= 2000000000;        
        readData();
        fun();
        std::cout << ansewer << "\n";
    }
    // std::cout << products.to_string() << "\n\n";
    // for (int i=0; i<R; i++) {
    //     std::cout << cookingMasks[i].to_string() << "\n";
    // }
    return 0;
}
