#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define PHILOSOPHERS 5

const int forksNum = PHILOSOPHERS + 1;

pid_t philosophers[PHILOSOPHERS];
pid_t mainPid;
sem_t * forks[PHILOSOPHERS + 1];

void myUnlink() {
    char buf[50];
    for (int i=0; i<forksNum; i++) {
        sprintf(buf, "sem_%d", i);
        assert( sem_close(forks[i]) == 0);
        if( sem_unlink(buf) != 0) {
            handle_error("unlink");
        }
    }
}

void handler(int sigNum) {
    assert(sigNum == SIGINT);
    assert(mainPid == getpid());
    puts("SIGINT");
    if (kill(0, SIGKILL) != 0) {
        handle_error("kill");
    }
    myUnlink();
}



void think() {
    usleep(10000 * (rand() % 40));
}

void eat() {
    think();
}

void take_forks(int * i) {
    if(*i == 0) {
        sem_wait(forks[*i % PHILOSOPHERS ]);
        sem_wait(forks[(*i + 1) % PHILOSOPHERS]);
    } else {
        sem_wait(forks[(*i + 1) % PHILOSOPHERS]);
        sem_wait(forks[*i % PHILOSOPHERS ]);
    }
}

void put_forks(int * i) {
    sem_post(forks[*i % PHILOSOPHERS ]);
    sem_post(forks[(*i + 1) % PHILOSOPHERS]);
}


void * philosopher(int * i) {
    // while (1) {
        think();
        take_forks(i);
        printf("Eating %d\n", getpid());
        //ASSERT_TESTS
            int value;
            sem_getvalue(forks[*i % PHILOSOPHERS], &value);
            assert(value == 0);
            sem_getvalue(forks[(*i + 1) % PHILOSOPHERS], &value);
            assert(value == 0);            
        eat();
        put_forks(i);
    // }
    printf("Exiting %d\n", getpid());
    exit(EXIT_SUCCESS);
}

void testSem() {
    for (int i=0; i<PHILOSOPHERS; i++) {
    //ASSERT_TESTS
            int value;
            sem_getvalue(forks[i % PHILOSOPHERS], &value);
            assert(value == 1);
            sem_getvalue(forks[(i + 1) % PHILOSOPHERS], &value);
            assert(value == 1);  
   }    
}


int main() {
    // myUnlink();
    // return 0;
    srand (time(NULL));
    
    for (int i=0; i<forksNum; i++) {
        forks[i] = NULL;
        char buf[50];
        sprintf(buf, "sem_%d",i);
        forks[i] = sem_open( buf
                    , O_CREAT | O_EXCL
                    ,  S_IRUSR | S_IWUSR
                    , 1);
        if (forks[i] == SEM_FAILED) {
            handle_error("sem");
            myUnlink();
        }
    }
    int v;
    sem_getvalue(forks[0], &v);
    printf("value:%d\n", v);

    int args[PHILOSOPHERS];
    for (int i = 0; i < PHILOSOPHERS; i++){
        args[i] = i;
        philosophers[i] = fork();
        assert(philosophers[i] >= 0);
        if (philosophers[i] == 0) {
            assert(mainPid != getpid());
            philosopher(&args[i]);
        }
    }
    for (int i = 0; i < PHILOSOPHERS; i++){
        printf( "%d\n",philosophers[i]);

    }

    mainPid = getpid();
    struct sigaction sigint_sigaction; 
    memset(&sigint_sigaction, 0, sizeof(struct sigaction));
    sigint_sigaction.sa_handler = handler;
	sigaction(SIGINT, &sigint_sigaction, NULL);

    pid_t pidExit;
    while ((pidExit = wait(NULL))) {
        if (errno == ECHILD) {
            break;
        }
    } 
    myUnlink();


    return 0;
}