#include <stdio.h>
#include <signal.h>
/*===============================================================
[Function Name] : SigIntHandler(int signo)
[Description]   :
	- SIGINT라는 시그널이 오면 문자열을 출력하고 종료하하는 함수이다
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
SigIntHandler(int signo)
{
	printf("Received a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}
/*===============================================================
[Program Name] : sig1.c
[Description]  :
	- 이 프로그램은 sigint라는 종료하는 ctrl+c 커맨드를 받으면 종료하는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
	- signal() //signal 핸들러 등록 메소드
	- pause() // signal을 기다리는 메소
[특기사항]     :
==================================================================*/
main()
{
	signal(SIGINT, SigIntHandler);

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
