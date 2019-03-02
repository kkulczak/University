#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <cstring>

using namespace std;




int main() {
    unsigned long long int a, b, res, i;
    scanf("%llu %llu", &a, &b);
    res = 1;
    i = a + 1;
    for (; i <= b && i <= a + 40; i ++) {
        res = (res * i) % 10;
    }
    if (i != b + 1) res = 0;
    printf("%llu\n", res);
    return 0;
}
