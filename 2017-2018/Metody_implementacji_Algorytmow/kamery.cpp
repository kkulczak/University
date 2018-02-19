#include <iostream>
#include <cstdio>

#define SIZE 100005

size_t windowSize, N;
size_t camerasCounter = 0;
size_t a,b;
bool tab[SIZE];
size_t result =0;

void read_data() {
    for (size_t i=0; i< SIZE; i++)
        tab[i] = 0;
    size_t k;
    scanf("%zu %zu %zu", &N, &k, &windowSize);
    for(size_t i=0; i<k; i++) {
        size_t temp;
        scanf("%zu", &temp);
        tab[temp] = 1;
    }
}
void insertCamera(int howMany) {
    for(size_t i=0; i<windowSize ; i++){
        if(howMany == 0)
            return;
        if( tab[b-i] == 0 ) {
            tab[b-i] = 1;
            howMany--;
            camerasCounter++;
            result++;
        }
    }
}

void initWindow() {
    a = 0;
    b = windowSize - 1;
    for (size_t i=0; i< windowSize; i++) {
        camerasCounter += tab[i];
    }
    if(camerasCounter < 2)
        insertCamera(2 - camerasCounter);
}


void step() {
    camerasCounter -= tab[a];
    a++;
    b++;
    camerasCounter += tab[b];
    if(camerasCounter < 2)
        insertCamera(2 - camerasCounter);
}

void showTab() {
    for(size_t i=0; i<16; i++) {
        std::cout << tab[i] ;
    }
    std::cout << "\n";
}



int main() {
    read_data();
    initWindow();
    while(b != N-1) {
        // std::cout <<"camerasCounter: " << camerasCounter << "\n";
        // showTab();
        step();
    }
    std::cout << result << "\n";
}
