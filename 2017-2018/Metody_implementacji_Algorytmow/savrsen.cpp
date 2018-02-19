#include <cstdio>
#include <iostream>
#include <cmath>

#define MaxTab 1000005

int tab[MaxTab];
int first,last;

void init();
void print();
unsigned long long int reduce();

int main()
{
    scanf("%d %d", &first, &last);
    init();
    for (int it = 2; it <= last; it ++) {
        int startIndex =  it * 2;
        for (int i=startIndex; i <= last && i < MaxTab; i += it ){
            tab[i] += it;
        }
    }

    // for(int i=first; i<=last; i++){
    //     tab[i] = tab[i] < i ? i - tab[i] : tab[i] - i;
    // }

    // print();

    printf("%llu\n", reduce());

    return 0;
}


void init() {
    tab[1] = 0;
    for (int i = 2; i < MaxTab; ++i) {
        tab[i] = 1;
    }
}


void print() {
    for(int i=first; i<=last; i++){
        std::cout << tab[i] << " ";
    }
    std::cout << "\n";
}

unsigned long long int reduce() {
    unsigned long long int res=0;
    for(int i=first; i<=last; i++){
        res += std::abs( i - tab[i]);
        // res += tab[i];
    }
    return res;
}
