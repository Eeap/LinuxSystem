#include <stdio.h>
#include <signal.h>
/*===============================================================
[Function Name] : SigAlarmHandler(int signo)
[Description]   :
    - SIGALRM라는 시그널이 오면 return을 해서 signal을 기다리고 있는pause메소드를 깨운다.
[Input]         :
[Output]        :
[Call By]       :
    mysleep()
[Calls]         :
[Given]         :
    int signo //signal 번호
[Returns]       :
==================================================================*/
void
SigAlarmHandler(int signo)
{
	/* nothing to do, just return to wake up the pause */
	return;
}
/*===============================================================
[Function Name] : mysleep(unsigned int nsecs)
[Description]   :
    - SIGALRM라는 시그널이 오면 처리하는 핸들러를 signal을 통해 등록하고 alarm을 통해서 nsecs 이후에 알람시그널을 발생하도록 한다.
	- 그 이후 pause를 통해 시그널을 기다리고 alarm(0)을 통해 이전 남은 알람 시간을 반환한다. 
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
	signal() //signal핸들러 등록 메소드
	alarm() // 알람 시그널을 발생시키는 메소드
	pause() // 시그널을 기다리는 메소드
[Given]         :
    unsigned int nsecs // alarm메소드에 넣을 시간
[Returns]       :
==================================================================*/
unsigned int
mysleep(unsigned int nsecs)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return nsecs;
	}

	alarm(nsecs);

	pause();

	return alarm(0);
}
/*===============================================================
[Program Name] : mysleep.c
[Description]  :
    - 이 프로그램은 sleep할 시간만큼 sleep시키는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
	mysleep() //입력받은 시간만큼 sleep시키는 메소드
[특기사항]     :
==================================================================*/
main()
{
	printf("Wait for 5 seconds...\n");

	mysleep(5);
}

