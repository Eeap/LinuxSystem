#include <stdio.h>
#include <signal.h>
/*===============================================================
[Function Name] : SigUsrHandler(int signo)
[Description]   :
    - user defined을 위한 시그널인 SIGUSR1, SIGUSR2라는 시그널이 오면 문자열을 출력하고 이외의 다른 시그널이 오면 종료한다. 
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
    - exit() //시스템 종료 메소드
[Given]         :
    int signo //signal 번호
[Returns]       :
==================================================================*/
void
SigUsrHandler(int signo)
{
	if (signo == SIGUSR1)  {
		printf("Received a SIGUSR1 signal\n");
	}
	else if (signo == SIGUSR2)  {
		printf("Received a SIGUSR2 signal\n");
	}
	else  {
		printf("Received unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}
/*===============================================================
[Program Name] : sig2.c
[Description]  :
    - 이 프로그램은 SIGUSR1과 SIGUSR2라는 시그널을 받으면 해당 시그널 핸들러를 등록해서 처리하는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
    - signal() //signal 핸들러 등록 메소드
    - pause() // signal을 기다리는 메소
[특기사항]     :
==================================================================*/
main()
{
	if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	for ( ; ; )
		pause();
}
