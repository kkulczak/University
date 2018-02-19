#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define NAME_CRITSEC "Critsec"
#define NAME_ISEMPTY "IsEmpty"
#define NAME_ISFULL "IsFull"

#define SAVEGES 5000
#define GOULASH 4000
#define MISTIONARIES 1000

int portions = GOULASH;
sem_t critsec;
sem_t isEmpty;
sem_t isFull;


void *coocker(){
    for(int i=0; i< MISTIONARIES; i++) {
        sem_wait(&isEmpty);
            //TESTS_ASSERTS
            assert(portions == 0);
        portions = GOULASH;
        sem_post(&isFull);
    }
    exit(EXIT_SUCCESS);
}

void *savage() {
    int value;
    while(1) {
        sem_wait(&critsec);
        if (portions == 0) {
            sem_post(&isEmpty);
            sem_wait(&isFull);
            //TESTS_ASSERTS
                assert(portions == GOULASH);
                sem_getvalue(&isEmpty, &value);
                assert(value == 0);
        }
        portions--;
        sem_post(&critsec);
    }
}

void initSem(sem_t * sem, int value){;
    assert(sem_init(sem, 0, value) == 0);
}

void init() {
    initSem(&critsec, 1);
    initSem(&isEmpty, 0);
    initSem(&isFull, 0);
}

int main() {
    pthread_t child;
    init();
    assert(pthread_create(&child, NULL, coocker, NULL) == 0);
    for (int i=0; i < SAVEGES; i++) {
        assert(pthread_create(&child, NULL, savage, NULL) == 0);
    }
    pause();
}
