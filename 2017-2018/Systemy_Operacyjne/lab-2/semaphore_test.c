#define PROCESESS 300
#define LOOP 300

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <sys/wait.h>

#include "semaphore.h"

int tally = 0;
int semaphoreFd;
pthread_t pthreads[PROCESESS];
sem_t semaphore;
sem_t * sem = &semaphore;

void* incTally () {
    for (int i=0; i<LOOP; i++) {
        sem_wait(sem);
        //ASSERT_TESTS
            int value;
            sem_getvalue(sem, &value);
            assert(value == 0);
        tally++;
        sem_post(sem);
    }
    pthread_exit(EXIT_SUCCESS);
}

void spawnChildren() {
    for (int i=0; i < PROCESESS; i++ ) {
        pthread_create(&pthreads[i], NULL, incTally, NULL);
    }
    for (int i=0; i < PROCESESS; i++ ) {
        assert(pthread_join(pthreads[i], NULL) == 0);
    }
}


int main () {
    sem_init(sem, 1);
    spawnChildren();
    assert( tally == PROCESESS * LOOP);
    return 0;
}
