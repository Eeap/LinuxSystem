#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "prodcons.h"
/*===============================================================
[Program Name] : producer.c
[Description]  :
	- 이 프로그램은 shared memory에 있는 buffer를 가져와서 데이터를 buf에 추가하는 프로그램이다
	- shmget을 통해 shmid를 가져오고 그걸로 shmat해서 pBuf포인터를 가져온다. 그다음 pBuf의 카운터가 MAX_BUF에 도달하면 busy waiting을 하고 그렇지 않으면 pBuf를 이용해서 데이터를 넣는다.
	- NLOOPS만큼 끝난 뒤에는 shmctl로 shared memory를 삭제한다.
[Input]        :
[Output]       :
[Calls]        :
    shmget() // shared memory를 만들거나 아이디를 가져오는 함수
    shmat() // shared memory에 attach하는 함수
    shmctl() // shared memory를 control하는 함수
[특기사항]     :
==================================================================*/
main()
{
	BoundedBufferType	*pBuf;
	int					shmid, i, data;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	srand(0x8888);
	for (i = 0 ; i < NLOOPS ; i++)  {
		if (pBuf->counter == MAX_BUF)  {
			printf("Producer: Buffer full. Waiting.....\n");
			while (pBuf->counter == MAX_BUF)
				;
		}

		printf("Producer: Producing an item.....\n");
		data = (rand()%100)*10000;
		pBuf->buf[pBuf->in].data = data;
		pBuf->in = (pBuf->in + 1) % MAX_BUF;
		pBuf->counter++;

		usleep(data);
	}

	printf("Producer: Produced %d items.....\n", i);

	sleep(2);
	printf("Producer: %d items in buffer.....\n", pBuf->counter);
	
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}

