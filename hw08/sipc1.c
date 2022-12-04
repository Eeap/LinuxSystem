    if ((emptySemid = semInit(EMPTY_SEM_KEY)) < 0)  {
        fprintf(stderr, "semInit failure\n");
        exit(1);
    }
    if ((fullSemid = semInit(FULL_SEM_KEY)) < 0)  {
        fprintf(stderr, "semInit failure\n");
        exit(1);
    }
    if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
        fprintf(stderr, "semInit failure\n");
        exit(1);
    }
    if (semWait(emptySemid) < 0)  {
        fprintf(stderr, "semWait failure\n");
        exit(1);
    }
    if (semWait(mutexSemid) < 0)  {
        fprintf(stderr, "semWait failure\n");
        exit(1);
    }
    pData = ptr + sizeof(int);
    printf("Received request: %s.....", pData);
    sprintf(pData, "This is a reply from %d.", getpid());
    if (semPost(mutexSemid) < 0)  {
        fprintf(stderr, "semPost failure\n");
        exit(1);
    }
    if (semPost(fullSemid) < 0)  {
        fprintf(stderr, "semPost failure\n");
        exit(1);
    }

    sleep(5);
    if (semDestroy(emptySemid) < 0)  {
        fprintf(stderr, "semDestroy failure\n");
    }
    if (semDestroy(fullSemid) < 0)  {
        fprintf(stderr, "semDestroy failure\n");
    }
    if (semDestroy(mutexSemid) < 0)  {
        fprintf(stderr, "semDestroy failure\n");
    }
    if (shmctl(shmid, IPC_RMID, 0) < 0)  {
        perror("shmctl");
        exit(1);
    }
}
