#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include "shm.h"
#include "semlib.h"


int                 emptySemid, fullSemid,shmid;

int Calc(int number) {
	int data;
    BoundedBufferType   *pBuf;

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
	pBuf->data = number;
	if (semPost(emptySemid) < 0)  {
		fprintf(stderr, "semPost failure\n");
		exit(1);
	}
	if (semWait(fullSemid) < 0)  {
		fprintf(stderr, "semWait failure\n");
		exit(1);
	}
	data = pBuf->data;
	return data;
}

main(int argc, char* argv[])
{
	if (argc != 2) {
        perror("argc");
        exit(1);
    }
	int		data;
	data = Calc(atoi(argv[1]));
	printf("Calc = %d\n",data);
}
