#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
/*===============================================================
[Program Name] : wait.c
[Description]  : 
	- fork를 통해 자식 프로세스를 만들고 부모 프로세스의 경우엔 wait을 통해 자식 프로세스가 끝날때까지 기다렸다가 작업을 수행한다.
	- 자식 프로세스의 경우엔 내용을 출력하고 sleep을 통해 2초 기다렸다가 끝난다.
[Input]        :
[Output]       :
[Calls]        :            
	fork() //현재 프로세스와 똑같은 프로세스를 만드는 함수
    wait() //만든 자식 프로세스가 종료될 떄가지 기다리는 함수
	perror() // 에러메시지 출력
	sleep() //해당 시간만큼 재운다
[특기사항]     : 
==================================================================*/
main()
{
    pid_t	pid;
    int		status;

    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        printf("I'm a child\n");
        sleep(2);
    }
    else  {
        wait(&status);
        printf("A child killed with %d status\n", status);
    }
}