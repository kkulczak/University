#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define ROUNDS 500
#define HORSES 1000


#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

typedef struct {
    sem_t critsec;
    sem_t inDoor;
    sem_t outDoor;
    int barierSize;
    int insideCount;
} bar_t;

bar_t * raceBarier;

void bar_init(bar_t *bar, int n)
{
    if (sem_init(&bar->critsec, 1, 1) < 0)
        handle_error("sem_init critsec");
    if (sem_init(&bar->inDoor, 1, n) < 0)
        handle_error("sem_init inDoor");
    if (sem_init(&bar->outDoor, 1, 0) < 0)
        handle_error("sem_init outDoor");
    bar->barierSize = n;
    bar->insideCount = 0;
}

int getInDoor(bar_t * bar) {
    int res;
    assert(sem_getvalue(&bar->inDoor, &res) == 0);
    return res;
}

int getOutDoor(bar_t * bar) {
    int res;
    assert(sem_getvalue(&bar->outDoor, &res) == 0);
    return res;
}

void bar_wait(bar_t *bar)
{
    assert(sem_wait(&bar->inDoor) == 0);
    //Critsec after first gate
    assert(sem_wait(&bar->critsec) == 0);
    int inDoorValue;
    assert(sem_getvalue(&bar->inDoor, &inDoorValue) == 0);
    bar->insideCount++;
    if (bar->insideCount == bar->barierSize) {
        for (int i = 0; i < bar->barierSize; i++) {
            assert(sem_post(&bar->outDoor) == 0);
        }
        // TESTS_ASSERTS
        assert(bar->insideCount == bar->barierSize);
        assert(getInDoor(bar) == 0);
    }
    assert(sem_post(&bar->critsec) == 0);
    
    assert(sem_wait(&bar->outDoor) == 0);
    //critsec after second gate
    assert(sem_wait(&bar->critsec) == 0);    
    bar->insideCount--;
    if (bar->insideCount == 0) {
        for (int i = 0; i < bar->barierSize; i++) {
            assert(sem_post(&bar->inDoor) == 0);
        }
        // TESTS_ASSERTS
        assert(bar->insideCount == 0);
        assert(getOutDoor(bar) == 0);
    }
    assert(sem_post(&bar->critsec) == 0);
}

void bar_destroy(bar_t *bar) {
    if (sem_destroy(&bar->critsec) < 0) 
        handle_error("destroy critsec");
    if (sem_destroy(&bar->inDoor) < 0) 
        handle_error("destroy inDoor");
    if (sem_destroy(&bar->outDoor) < 0) 
        handle_error("destroy outDoor");
}

int bar_fd;

bar_t *initializeBarrier(int n) {
  bar_t *bar;
  bar_fd = shm_open("Barier", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (bar_fd == 0) {
      handle_error("shm_open");
  }
  ftruncate(bar_fd, sizeof(bar_t));
  bar = mmap( NULL, sizeof(bar_t)
                , PROT_READ | PROT_WRITE
                , MAP_SHARED
                , bar_fd
                , 0
                );
  if (bar == NULL) {
      handle_error("mmap");
  }
  bar_init(bar, n);
  return bar;
}

void destroyBarrier(bar_t * bar) {
  bar_destroy(bar);
  munmap(bar, sizeof(bar_t));
  shm_unlink("Barier");
}

void startRace() {
    for (int i=0; i<ROUNDS; i++) {
        bar_wait(raceBarier);
    }
    exit(EXIT_SUCCESS);
}

void spawnHorses(int amount) {
    for (int i=0; i<amount; i++) {
        pid_t childPid = fork();
        if (childPid < 0)
            handle_error("fork");
        if (childPid == 0) {
            startRace();
        }
    }
    pid_t pidExit;
    while ((pidExit = wait(NULL))) {
        if (errno == ECHILD) {
            break;
        }
    }   
}

int main() {
    raceBarier = initializeBarrier(HORSES);
    spawnHorses(HORSES);
    destroyBarrier(raceBarier);
}