#ifndef SEM
#define SEM 1

#include <pthread.h>

#define handle_error(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct {
    pthread_mutex_t critsec;
    pthread_cond_t waiters;
    int count;
} sem_t;

void sem_init(sem_t *sem, unsigned value);
void sem_wait(sem_t *sem);
void sem_post(sem_t *sem);
void sem_getvalue(sem_t *sem, int *sval);

#endif