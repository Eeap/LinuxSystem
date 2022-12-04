#include <stdio.h>
#include "synclib.h"

#define	NLOOPS	5


main()
{
	int		i;
	pid_t	pid;

	TELL_WAIT();
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			TELL_CHILD();
			printf("Parent: Tell to child\n");
			printf("Parent: Wait for child to tell\n");
			WAIT_CHILD();
		}
	}
	else  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			printf("Child: Wait for parent to tell\n");
			WAIT_PARENT();
			TELL_PARENT();
			printf("Child: Tell to parent\n");
		}
	}
}
