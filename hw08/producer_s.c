    srand(0x8888);
    for (i = 0 ; i < NLOOPS ; i++)  {
        if (semWait(emptySemid) < 0)  {
            fprintf(stderr, "semWait failure\n");
            exit(1);
        }
        if (semWait(mutexSemid) < 0)  {
            fprintf(stderr, "semWait failure\n");
            exit(1);
        }

        printf("Producer: Producing an item.....\n");
        data = (rand()%100)*10000;
        pBuf->buf[pBuf->in].data = data;
        pBuf->in = (pBuf->in + 1) % MAX_BUF;
        pBuf->counter++;

        if (semPost(mutexSemid) < 0)  {
            fprintf(stderr, "semPost failure\n");
            exit(1);
        }
        if (semPost(fullSemid) < 0)  {
            fprintf(stderr, "semPost failure\n");
            exit(1);
        }
        usleep(data);
    }

    printf("Producer: Produced %d items.....\n", i);

    sleep(2);
    printf("Producer: %d items in buffer.....\n", pBuf->counter);

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
