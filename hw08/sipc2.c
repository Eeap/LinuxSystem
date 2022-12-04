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

    if (semInitValue(emptySemid, MAX_BUF) < 0)  {
        fprintf(stderr, "semInitValue failure\n");
        exit(1);
    }
    if (semInitValue(fullSemid, 0) < 0)  {
        fprintf(stderr, "semInitValue failure\n");
        exit(1);
    }
    if (semInitValue(mutexSemid, 1) < 0)  {
        fprintf(stderr, "semInitValue failure\n");
        exit(1);
    }
    if (semWait(fullSemid) < 0)  {
        fprintf(stderr, "semWait failure\n");
        exit(1);
    }
    if (semWait(mutexSemid) < 0)  {
        fprintf(stderr, "semWait failure\n");
        exit(1);
    }
    pInt = (int *)ptr;
    pData = ptr + sizeof(int);
    sprintf(pData, "This is a request from %d.", getpid());
    printf("Sent a request.....");
    if (semPost(mutexSemid) < 0)  {
        fprintf(stderr, "semPost failure\n");
        exit(1);
    }
    if (semPost(emptySemid) < 0)  {
        fprintf(stderr, "semPost failure\n");
        exit(1);
    }
    sleep(2);
}
