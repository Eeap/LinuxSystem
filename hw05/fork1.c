#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*===============================================================
[Program Name] : fork1.c
[Description]  : 
	- fork를 통해 현재 프로세스와 똑같은 프로세스를 하나 만든다
	- pid가 0일 경우 자식을 의미하고 0보다 클 경우 부모 프로세스를 의미한다
[Input]        :
[Output]       :
[Calls]        :	        
	fork() // 현재 프로세스와 똑같은 프로세스를 하나 더 만드는 함수
	getpid() //process id 반환
	getppid() //parent process id 반환
	perror() // 에러메시지 출력
[특기사항]     : 
==================================================================*/

main()
{
    int		pid;

    if ((pid= fork())< 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        /* child */
        printf("I am %d. My parent is %d.\n", getpid(), getppid());
    }
    else  {
        /* parent */
        printf("I am %d. My child is %d.\n", getpid(), pid);
    }
}