#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "semaphore.h"
#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define PHILOSOPHERS 500

const int forksNum = PHILOSOPHERS + 1;

pthread_t philosophers[PHILOSOPHERS];

sem_t forks[PHILOSOPHERS + 1];


void handler(int sigNum) {
    assert(sigNum == SIGINT);
    for ( int i=0; i<PHILOSOPHERS; i++) {
        
        if(pthread_cancel(philosophers[i]) != 0);
        handle_error("cance");
    }
}

void think() {
    usleep(10000 * (rand() % 40));
}

void eat() {
    think();
}

void take_forks(int * i) {
    if(*i == 0) {
        sem_wait(&forks[*i % PHILOSOPHERS ]);
        sem_wait(&forks[(*i + 1) % PHILOSOPHERS]);
    } else {
        sem_wait(&forks[(*i + 1) % PHILOSOPHERS]);
        sem_wait(&forks[*i % PHILOSOPHERS ]);
    }
}

void put_forks(int * i) {
    sem_post(&forks[*i % PHILOSOPHERS ]);
    sem_post(&forks[(*i + 1) % PHILOSOPHERS]);
}


void * philosopher(int * i) {
    // while (1) {
        think();
        take_forks(i);
        //ASSERT_TESTS
            int value;
            sem_getvalue(&forks[*i % PHILOSOPHERS], &value);
            assert(value == 0);
            sem_getvalue(&forks[(*i + 1) % PHILOSOPHERS], &value);
            assert(value == 0);            
        eat();
        put_forks(i);
    // }
    pthread_exit(EXIT_SUCCESS);
}



int main() {
    srand (time(NULL));
    
    struct sigaction sigint_sigaction; 
    memset(&sigint_sigaction, 0, sizeof(struct sigaction));
    sigint_sigaction.sa_handler = handler;
	sigaction(SIGINT, &sigint_sigaction, NULL);

    for (int i=0; i < forksNum; i++) {
        sem_init(&forks[i], 1);
    }

    int args[PHILOSOPHERS];
    for (int i = 0; i < PHILOSOPHERS; i++){
        args[i] = i;
        assert(pthread_create(&philosophers[i], NULL, (void* (*)(void*)) philosopher, &args[i] ) == 0);
    }

    for (int i=0; i < PHILOSOPHERS; i++) {
        assert(pthread_join(philosophers[i], NULL) == 0);
    }

    return 0;
}