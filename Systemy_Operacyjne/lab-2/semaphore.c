#include "semaphore.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>


void sem_init(sem_t *sem, unsigned value){
    memset(sem,0,sizeof(sem_t));
    // mutex init
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK_NP);
    pthread_mutex_init(&sem->critsec, &mutexattr);
    // cond var init
    pthread_cond_init( &sem->waiters, NULL);

    sem->count = value;

}
void sem_wait(sem_t *sem) {
    assert(pthread_mutex_lock(&sem->critsec) == 0);
    while (sem->count == 0) {
        pthread_cond_wait(&sem->waiters, &sem->critsec);
    }
    sem->count--;
    assert(pthread_mutex_unlock(&sem->critsec) == 0);
}
void sem_post(sem_t *sem) {
    assert(pthread_mutex_lock(&sem->critsec) == 0);
    sem->count++;
    // if (sem->count == 0) {
        pthread_cond_broadcast(&sem->waiters);
    // }
    assert(pthread_mutex_unlock(&sem->critsec) == 0);
}


void sem_getvalue(sem_t *sem, int *sval) {
    *sval = sem->count;
}
