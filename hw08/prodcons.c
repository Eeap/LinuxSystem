
    srand(0x9999);

    if (sem_init(&EmptySem, 0, MAX_BUF) < 0)  {
        perror("sem_init");
        exit(1);
    }
    if (sem_init(&FullSem, 0, 0) < 0)  {
        perror("sem_init");
        exit(1);
    }
    if (sem_init(&MutexSem, 0, 1) < 0)  {
        perror("sem_init");
        exit(1);
    }

    if (pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL) < 0)  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL) < 0)  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_join(tid1, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(tid2, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    printf("Main    : %d items in buffer.....\n", Buf.counter);

    if (sem_destroy(&EmptySem) < 0)  {
        perror("sem_destroy");
    }
    if (sem_destroy(&FullSem) < 0)  {
        perror("sem_destroy");
    }
    if (sem_destroy(&MutexSem) < 0)  {
        perror("sem_destroy");
    }
}
