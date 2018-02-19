rw_lock init() {
    return {
        owner = NULL;
        readers = 0;
        critsec = init_mutex();
        noreaders = init_cv();
        nowriter = init_cv();
        writer = init_mutex();
    }
}

void rdlock(rw_lock name) {
    pthred_mutex_lock(name.critsec);
    while (name.owned != NULL) {
        pthread_cond_wait(name.nowriter);
    }
    readers++;
    pthred_mutex_unlock(name.critsec);
}

void wrlock(rw_lock name) {
    pthred_mutex_lock(name.writer);

    pthred_mutex_lock(name.critsec);
    while (readers > 0) {
        pthread_cond_wait(name.noreaders);
    }

    name.owner = thread_id();
    pthred_mutex_unlock(name.critsec);
}

void unlock(rw_lock name) {
    pthred_mutex_lock(name.critsec);
    if (name.owner == thread_id()) {
        name.owner == NULL;
        pthred_mutex_unlock(name.writer);
        pthread_cond_broadcast(name.nowriter);
    } else {
        name.readers--;
        if (name.readers == 0) {
            pthread_cond_signal(name.noreaders);
        }
    }
    pthred_mutex_unlock(name.critsec);
}
