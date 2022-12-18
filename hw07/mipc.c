#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include "synclib.h"
#include <errno.h>
#define	NLOOPS	10
#define	SIZE	sizeof(long)

/*===============================================================
[Function Name] : update(long *ptr)
[Description]   :
	- ptr를 하나 증가시켜서 그 포인터가 가리키는 값을 반환해주는 함수
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
[Given]         :
    long *ptr // long타입의 포인터
[Returns]       :
==================================================================*/
int
update(long *ptr)
{
	return ((*ptr)++);
}
/*===============================================================
[Program Name] : mipc.c
[Description]  :
    - 이 프로그램은 memory mapped file 방식과 부모와 자식 프로세스간의 파이프 방식을 이용해서 파일에 있는 데이터 내용을 부모와 자식이 번갈아가면서 읽는 프로그램이다
	- 먼저 읽을 파일을 오픈하고 그 파일을 메모리와 매핑한다. 그 다음 TELL_WAIT을 통해 파이프를 만들고 fork로 자식 프로세스를 생성한다. 이후 자식과 부모간의 TELL과 WAIT 함수를 이용해서 서로 번갈아가면서 호출하고 기다리는데 여기서 update라는 함수를 통해 파일의 내용을 출력하는 포인터를 하나씩 증가시킨다. 결과적으로 숫자가 하나씩 증가하면서 번갈아가면서 출력하는 작업을 한다
%%%% 수정 후 %%%%
	 - mmap 방식에서 shm를 이용한 방식으로 바꿔서 번갈아가면서 내용을 출력하는 방식으로 바꾼다.
	 - /dev/zero로 파일을 오픈하는 대신에 동일하게 이번에는 특수 파일의 시작번지인 0x00으로 shared memory의 id를 가져온다. 그 다음 attach하고 이후부터는 mmap방식과 똑같이 번갈아가면서 값을 출력한다.

[Input]        :
[Output]       :
[Calls]        :
    close() // 파일을 닫을 때 쓰는 함수
    open() // 파일을 오픈하는 함수
    mmap() // 메모리를 파일에 매핑하는 함수
	fork() // 자식 프로세스를 만드는 함수
	update() //포인터를 하나씩 증가시켜서 그 포인터가 가리키는 값을 반환해주는 함수
	TELL_WAIT() //파이프를 생성하는 함수
    TELL_CHILD() // 자식을 호출하는 함수(write작업을 하는 함수)
    WAIT_CHILD()// 자식을 기다리는 함수(read작업을 하는 함수)
    WAIT_PARENT() //부모를 기다리는 함수(read작업을 하는 함수)
    TELL_PARENT() //부모를 호출하는 함수(write작업을 하는 함수)
    shmget() // shared memory를 만들거나 아이디를 가져오는 함수
    shmat() // shared memory에 attach하는 함수
[특기사항]     :
==================================================================*/
main()
{
	int		i, counter,shmid;
	pid_t	pid;
	char	*ptr;

	if ((shmid = shmget(0x00, SIZE, (SHM_R|SHM_W))) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	TELL_WAIT();
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i += 2)  {
			if ((counter = update((long *) ptr)) != i)  {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			printf("Parent: counter=%d\n", counter);
			TELL_CHILD();
			WAIT_CHILD();
		}
	}
	else  {
		for (i = 1 ; i < NLOOPS ; i += 2)  {
			WAIT_PARENT();
			if ((counter = update((long *) ptr)) != i)  {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			printf("Child : counter=%d\n", counter);
			TELL_PARENT();
		}
	}
}
