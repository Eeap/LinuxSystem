        ThreadUsleep((rand()%100)*10000);
    }

    printf("Consumer: Consumed %d items.....\n", i);
    printf("Consumer: %d items in buffer.....\n", Buf.counter);

    pthread_exit(NULL);
}
/*===============================================================
[Program Name] : prodcons_t.c
[Description]  :
    - 이 프로그램은 Producer 쓰레드와 Consumer 쓰레드를 하나씩 생성해 하나의 프로세스에
서 쓰레드를 이용해서 버퍼에 데이터를 넣고 데이터를 빼는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
    - pthread_create() // thread를 생성하는 함수
    - pthread_join() // 특정 thread를 기다리는 함수
[특기사항]     :
==================================================================*/
main()
{
    pthread_t   tid1, tid2;

    srand(0x8888);

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
}
