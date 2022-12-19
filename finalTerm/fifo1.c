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




#define	MSG_REQUEST		1
#define	MSG_REPLY		2


typedef struct  {
	int		type;
	char	data[128];
} MsgType;


main()
{
	int			fd, n;
	MsgType		msg;


	if (mkfifo("./.myfifo", 0600) < 0)  {
		if (errno != EEXIST)  {
			perror("mkfifo");
			exit(1);
		}
	}

	if ((fd = open("./.myfifo", O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	while (1)  {
		if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
			if (errno == EINTR)  {
				continue;
			}
			else  {
				perror("read");
				exit(1);
			}
		}
		if (msg.type != MSG_REQUEST)
			continue;
		printf("FIFO1: Received a message: %s\n", msg.data);
		msg.type = MSG_REPLY;
		sprintf(msg.data, "%s", "Hi");
		write(fd, (char *)&msg, sizeof(msg));
		printf("FIFO1: Sent a message: %s\n",msg.data);
		sleep(3);
		break;
	}
	close(fd);
	remove("./.myfifo");
}
