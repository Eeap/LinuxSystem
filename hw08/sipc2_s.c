#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"
#include <stdlib.h>
#include <unistd.h>
/*===============================================================
[Program Name] : sipc2.c
[Description]  :
    - 이 프로그램은 shared memory를 이용해서 두 프로세스 간에 메시지를 주고받는 프로그램이다
    - shmget으로 먼저 shared memory의 id값을 가져온다. 그 다음 shmat을 통
해 해당 shared memory에 attach한다. 그 다음 세마포어의 값들을 initvalue함수를 통해 초기화해준다.
	- 그 다음 세마포어가 존재하면 세마포어를 하나 사용해서 critical section에 들어간다.
	- 데이터를 shared memory에서 읽어온 후 다시 응답 데이터를 쓴 뒤 post를 통해서 사용했던 세마포어를 반납한다. 

[Input]        :
[Output]       :
[Calls]        :
    shmget() // shared memory를 만들거나 아이디를 가져오는 함수
    shmat() // shared memory에 attach하는 함수
	semInit() // 세마포어를 초기화하는 함수
	semWait() // 세마포어 자원을 할당받는 함수
	semPost() // 세마포어 자원을 반납하는 함수
	semDestroy() // 세마포어를 삭제하는 함수
	semInitValue() // 세마포어의 value를 초기화하는 함수
[특기사항]     :
==================================================================*/

main()
{
	int		shmid;
	char	*ptr, *pData;
	int		*pInt;
	int		emptySemid, fullSemid, mutexSemid;

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
	pData = ptr + sizeof(int);
    printf("Received request: %s.....", pData);
    sprintf(pData, "This is a reply from %d.", getpid());
	if (semPost(mutexSemid) < 0)  {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	if (semPost(emptySemid) < 0)  {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
}

