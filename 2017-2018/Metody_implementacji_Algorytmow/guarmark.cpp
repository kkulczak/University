#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>

using namespace std;

typedef long int my_t;  

#define MAX_COWS 20
#define SIZE (1 << 20)
my_t N,H, MAX_INDEX, ansewer = -1;
my_t heigth[MAX_COWS];
my_t weigth[MAX_COWS];
my_t strength[MAX_COWS];

my_t setSafty[SIZE];
my_t setWeight[SIZE];
my_t setHeigth[SIZE];

void readData() {
    if ( scanf("%ld %ld", &N, &H)) {;}
    for (int i = 0; i < N; ++i)
    {
        if ( scanf("%ld %ld %ld", &heigth[i], &weigth[i], &strength[i])) {;}
    }
    MAX_INDEX = 1 << N;
    for (int i=0; i < SIZE; i++) {
        setSafty[i] = -1;
    }
}

void fun() {
    setSafty[0] = 0;
    setWeight[0] = 0;
    setSafty[0] = 2000000005;

    for (my_t i = 0; i < MAX_INDEX; i++ ) {
        bitset<MAX_COWS> set(i);
        for (my_t j=0; j < N; j++) {
            if (set.test(j)) {
                bitset<MAX_COWS> subSet = set;
                subSet.flip(j);
                if (setSafty[subSet.to_ulong()] < 0) {
                    continue;
                }
                my_t newSafty = strength[j] - setWeight[subSet.to_ulong()];
                if (newSafty < 0) {
                    continue;
                }
                my_t newSetSafty = min(newSafty, setSafty[subSet.to_ulong()]);
                setHeigth[i] = setHeigth[subSet.to_ulong()] + heigth[j];
                setWeight[i] = setWeight[subSet.to_ulong()] + weigth[j];
                setSafty[i] = max(newSetSafty, setSafty[i]);
                if (setHeigth[i] >= H) {
                    ansewer = max(setSafty[i], ansewer);
                }
            }
        }
    }
}


int main() {
    readData();
    fun();
    if (ansewer > 0) {
        printf("%ld\n", ansewer);
    } else {
        puts("Mark is too tall");
    }
    return 0;
}
