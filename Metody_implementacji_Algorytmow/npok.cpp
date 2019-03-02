#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
typedef long long int llu_t;
llu_t n, k, p;

#define min(a, b) \
    ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

void readData()
{
    if (scanf("%llu %llu %llu", &n, &k, &p))
    {
        ;
    }
}

llu_t euklides(llu_t a, llu_t b)
{
    llu_t x = 1;
    llu_t q = 0;
    llu_t r = 0;
    llu_t s = 1;

    while (b != 0)
    {
        llu_t c = a % b;
        llu_t quot = a / b;
        a = b;
        b = c;
        llu_t r_tmp = r;
        llu_t s_tmp = s;
        r = x - quot * r;
        s = q - quot * s;
        x = r_tmp;
        q = s_tmp;
    }
    if (x < 0)
        x += p;
    return x;
}

int main()
{
    if (scanf("%d", &N))
    {
        ;
    }
    for (int j = 0; j < N; j++)
    {
    llu_t res = 1, mian = 1;
        readData();
        for (llu_t i = n - k + 1; i <= n; i++)
        {
            res = (res * i) % p;
        }
        // cout << res << " res\n";
        for (llu_t i = 1; i <= k; i++)
        {
            mian = (mian * i) % p;
        }
        // cout << mian << " mian\n";
        // cout << euklides(mian, p) << " euklides\n";
        res = (res * euklides(mian, p)) % p;
        printf("%llu\n", res);
    }
    return 0;
}
