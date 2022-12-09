#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"
/*===============================================================
[Program Name] : producer_s.c
[Description]  :
	- 이 프로그램은 shared memory에 있는 buffer를 가져와서 데이터를 buf에 추가하는 프로그램이다
	- shmget을 통해 shmid를 가져오고 그걸로 shmat해서 pBuf포인터를 가져온다. 그다음 empty세마포어와 full세마포어, mutex세마포어를 semInit함수를 통해 초기화하고semWait함수를 통해 empty세마포어가 있는지 확인하고 있으면 그 다음으로 mutex 세마포어가 있는지 확인하고 있으면 critical section인 pBuf에 접근하다. 
	- pBuf를 이용해서 데이터를 넣고 mutex 세마포어를 반납한 뒤 full세마포어를 semPost로 하나 증가시켜준다.
	- NLOOPS만큼 끝난 뒤에는 empty세마포어와 full세마포어, mutex세마포어를 semDestroy로 삭제하고 shmctl로 shared memory를 삭제한다.
[Input]        :
[Output]       :
[Calls]        :
    shmget() // shared memory를 만들거나 아이디를 가져오는 함수
    shmat() // shared memory에 attach하는 함수
    shmctl() // shared memory를 control하는 함수
	semInit() // 세마포어를 초기화하는 함수
	semWait() // 세마포어 자원을 할당받는 함수
	semPost() // 세마포어 자원을 반납하는 함수
	semDestroy() // 세마포어를 삭제하는 함수
[특기사항]     :
==================================================================*/
main()
{
	BoundedBufferType	*pBuf;
	int					shmid, i, data;
	int					emptySemid, fullSemid, mutexSemid;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

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
