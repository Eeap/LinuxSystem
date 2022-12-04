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

    srand(0x9999);
    for (i = 0 ; i < NLOOPS ; i++)  {
        if (semWait(fullSemid) < 0)  {
            fprintf(stderr, "semWait failure\n");
            exit(1);
        }
        if (semWait(mutexSemid) < 0)  {
            fprintf(stderr, "semWait failure\n");
            exit(1);
        }
        printf("Consumer: Consuming an item.....\n");
        data = pBuf->buf[pBuf->out].data;
        pBuf->out = (pBuf->out + 1) % MAX_BUF;
        pBuf->counter--;

        if (semPost(mutexSemid) < 0)  {
            fprintf(stderr, "semPost failure\n");
            exit(1);
        }
        if (semPost(emptySemid) < 0)  {
            fprintf(stderr, "semPost failure\n");
            exit(1);
        }

        usleep((rand()%100)*10000);
    }

    printf("Consumer: Consumed %d items.....\n", i);
    printf("Consumer: %d items in buffer.....\n", pBuf->counter);
}
