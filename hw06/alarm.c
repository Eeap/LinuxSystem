#include <stdio.h>
#include <signal.h>

static unsigned int	AlarmSecs;

/*===============================================================
[Function Name] : SigAlarmHandler(int signo)
[Description]   : 
	- SIGALRM이라는 시그널이 오면 처리하기 위한 핸들러 함수이다.
	- 몇몇 운영체제에서는 핸들러가 한번 쓰여지면 재등록해야하기 때문에 재등록 해놓는다.
	- alarm을 통해 해당 시간 이후에 알람 시그널을 발생하도록 한다.
	- 알림 시그널이 발생할때마다 .을 하나씩 찍고 fflush를 통해 버퍼를 강제로 출력한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	signal() //signal핸들러 등록 메소드
    fflush() //버퍼를 비우는 메소드로 여기선 강제로 출력하는 메소드로 쓰인다.
	alarm() // 알람 시그널을 발생시키는 메소드
[Given]         :
    int signo //signal 번호
[Returns]       :
==================================================================*/
void
SigAlarmHandler(int signo)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	alarm(AlarmSecs);

	/* Do something */
	printf(".");
	fflush(stdout);

	return;
}
/*===============================================================
[Function Name] : SetPeriodicAlarm(unsigned int nsecs)
[Description]   : 
    - SIGALRM라는 시그널이 오면 처리하는 핸들러를 signal을 통해 등록하고 alarm을 통해서 nsecs 이후에 알람시그널을 발생하도록 한다.
[Input]         :
[Output]        :
[Call By]       :
	Main()
[Calls]         :
    signal() //signal핸들러 등록 메소드
    alarm() // 알람 시그널을 발생시키는 메소드
[Given]         :
    unsigned int nsecs // alarm메소드에 넣을 시간
[Returns]       :
==================================================================*/
int
SetPeriodicAlarm(unsigned int nsecs)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return -1;
	}

	AlarmSecs = nsecs;

	alarm(nsecs);

	return 0;
}
/*===============================================================
[Program Name] : alarm.c
[Description]  :
	- 이 파일은 알람이라는 시그널이 오면 미리 만들어놓은 시그널 핸들러를 통해서 시그널을 처리하는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
	- SetperiodicAlarm() : 알림이라는 시그널이 오면 미리만들어놓 시그널핸드러를 등록하고 파라미터로 입력받은 시간뒤에 alarm이라는 시스템콜을 통해 알람을 보낸다.
[특기사항]     :
==================================================================*/
main()
{
	printf("Doing something every one seconds\n");

	SetPeriodicAlarm(1);

	for ( ; ; )
		pause();
}
