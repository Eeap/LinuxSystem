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

void
CloseServer()
{
	if (semDestroy(emptySemid) < 0)  {
		fprintf(stderr, "semDestroy failure\n");
	}
	if (semDestroy(fullSemid) < 0)  {
		fprintf(stderr, "semDestroy failure\n");
	}
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
	exit(0);
}
main()
{
	int		data;
	BoundedBufferType	*pBuf;
	signal(SIGINT, CloseServer);

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
	if (semInitValue(emptySemid, 0) < 0)  {
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}
	if (semInitValue(fullSemid, 0) < 0)  {
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}
	while (1) {
		if (semWait(emptySemid) < 0)  {
     	   fprintf(stderr, "semWait failure\n");
        	exit(1);
    	}
    	data = pBuf->data;
    	int result=0;
    	int i;
    	for(i=0;i<data+1;i++) {
        	result+=i;
    	}
    	pBuf->data = result;
    	printf("Calc = %d\n",result);
    	if (semPost(fullSemid) < 0)  {
        	fprintf(stderr, "semPost failure\n");
        	exit(1);
    	}
	}
}
