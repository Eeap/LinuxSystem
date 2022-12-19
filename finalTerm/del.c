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
void del(char str[])
{
	int len = sizeof(str);
	char temp[len];
	int i;
	for(i=1; i<str[i]!='\0';i++) {
		temp[i-1]=str[i];
	}
	puts(temp);
	temp[i-1] = str[i];
	strcpy(str,temp);
}
main()
{
	char str[20] = "Hello";
	del(str);
	puts(str);
} 
