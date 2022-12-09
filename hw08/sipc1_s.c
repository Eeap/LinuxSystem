#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"
/*===============================================================
[Program Name] : sipc1_s.c
[Description]  :
    - 이 프로그램은 shared memory를 이용해서 두 프로세스 간에 메시지를 주고받는 프로그램이다
	- shmget으로 먼저 shared memory의 id값을 가져온다. 그 다음 shmat을 통해 해당 shared memory에 attach한다. 그 다음 세마포어를 이용해서 critical section에 들어가고 flag인 4바이트 이후부터 shared memory에  데이터를 입력한다.
	- 데이터를 다 입력한 뒤에 post를 이용해서 세마포어를 반납하고 full세마포어를 하나 추가한다.
	- 데이터의 전ㄴ송을 마친 뒤에는 세마포어를 삭제하고 shared memory도 삭제한다.
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
	int		shmid;
	char	*ptr, *pData;
	int		*pInt;
	int emptySemid, fullSemid, mutexSemid;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
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
	if (semWait(emptySemid) < 0)  {
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
    printf("Send a request data...\n");
	if (semPost(mutexSemid) < 0)  {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	if (semPost(fullSemid) < 0)  {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	
	sleep(2);
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
