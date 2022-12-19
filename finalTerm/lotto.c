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
int count;
int code;
int arr[6];
void
SigCHLDHandler(int signo)
{
	printf("\n%d\n",count);
	arr[code]=count;
	code++;
	if (code == 6) {
		printf("Lotto number: %d, %d, %d, %d, %d, %d\n",
				arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
		exit(0);
	}
}
main()
{
	signal(SIGINT,SigCHLDHandler);
	code = 0;
	count=1;
	while (1) {
		count = (count%45) +1;
	}
}
