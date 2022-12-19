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
#include "tcp.h"
int	Sockfd;
void
CloseServer()
{
	close(Sockfd);

	exit(0);
}
main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;
	int pid;
	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5);


	cliAddrLen = sizeof(cliAddr);
	while (1)  {
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
			perror("accept");
			exit(1);
		}
		if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
           	perror("read");
           	exit(1);
       	}
		int cnt = msg.data;
		int i;
		int result = 0;
		for (i=0;i<cnt+1;i++) {
			result+=i;
		}
		printf("Calc = %d\n",result);
       	msg.type = MSG_REPLY;
       	msg.data=result;
       	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
           	perror("write");
           	exit(1);
       	}
       	usleep(10000);
       	close(newSockfd);
		
	}
}
