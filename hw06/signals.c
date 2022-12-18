#include <stdio.h>
#include <signal.h>
#include <pthread.h>
/*===============================================================
[Function Name] : SigCHLDHandler(int signo)
[Description]   :
    - SIGCHLD라는 시그널이 오면 문자열을 출력하는 함수이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
[Given]         :
    int signo //signal 번호
[Returns]       :
==================================================================*/
void
SigCHLDHandler(int signo)
{
    printf("Received a SIGCHLD \n");
}

/*===============================================================
[Program Name] : signals.c
[Description]  :
	- fork를 통해 자식 프로세스를 만들고 자식 프로세스가 종료되면 비동기 이벤트인 signal을 이용하여 해당 시그널에 대한 비동기 처리를 하는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
    - signal() //signal 핸들러 등록 메소드
	- fork() //자식프로세스를 만드는 메소드
[특기사항]     :
==================================================================*/
main()
{
	pid_t	pid;
	signal(SIGCHLD,SigCHLDHandler);
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		printf("I'm a child\n");
	}
	else  {
		while(1)
			;
	}

}
