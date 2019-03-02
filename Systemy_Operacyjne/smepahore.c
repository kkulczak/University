sem_t SEM_INIT(int x) {
    return {
        critsec = init_mutex;
        waiters = init_cv;
        count = x;
        wakeups = 0;
    }
}

void sem_wait(sem_t name) {
    pthred_mutex_lock(name.critsec);
    if (name.count > 0) {
        name.count--;
    } else {
        name.wakeups++;
        pthread_cond_wait(name.waiters, name.critsec);
    }
    pthred_mutex_unlock(name.critsec);
}

void sem_post(sem_t name) {
    pthred_mutex_lock(name.critsec);
    if (name.count == 0 && name.wakeups > 0) {
        name.wakeups--;
        pthread_cond_signal(name.waiters);
    } else {
        name.count++;
    }
    pthred_mutex_unlock(name.critsec);
}
