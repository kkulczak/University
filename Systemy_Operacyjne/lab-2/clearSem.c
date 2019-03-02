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

#define PHILOSOPHERS 1000

const int forksNum = PHILOSOPHERS + 1;

pid_t philosophers[PHILOSOPHERS];

sem_t * forks[PHILOSOPHERS + 1];

int main() {
    char buf[50];
    for (int i=0; i<forksNum; i++) {
        sprintf(buf, "sem_%d", i);
        assert( sem_unlink(buf) == 0);
    }
    return 0;
}