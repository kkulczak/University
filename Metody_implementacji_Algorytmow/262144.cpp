
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

#define SIZE (262144 + 5)
#define RANGE 80

my_t N;
my_t data[SIZE];
my_t dp[RANGE][SIZE];



void readData() {
    memset(data, -1, sizeof(data));
    memset(dp, -1, sizeof(dp));
    if ( scanf("%lld", &N)) {;}
    for (int i=0; i< N; i++) {
        if ( scanf("%lld", &data[i])) {;}
    }
}

int main() {
    readData();
    my_t ansewer = 0;
    for (my_t i = 0; i <= RANGE; i++) {
        for (my_t j = 0; j < N; j++) {
            if (data[j] == i) {
                dp[i][j] = j + 1;
                ansewer = std::max(ansewer, i);
                continue;
            }
            
            if (i == 0) {
                continue;
            }
            
            if (dp[i - 1][j] == -1 || dp[i - 1][dp[i - 1][j]] == -1) {
                continue;
            }
            
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
            ansewer = std::max(ansewer, i);
        }
    }
    printf("%lld\n", ansewer);
    return 0;
}

