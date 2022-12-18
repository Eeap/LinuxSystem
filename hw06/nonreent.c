#include <stdio.h>
#include <signal.h>
#include <pwd.h>
/*===============================================================
[Function Name] : MyAlarmHandler(int signo)
[Description]   :
    - SIGALRM라는 시그널이 오면 처리하는 핸들러를 signal을 통해 등록하고 alarm을 통해서 해당 시간 이후에 알람시그널을 발생하도록 한다.
    - 그 이후 getpwnam을 통해 root 사용자의 정보를 얻어온다. 
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
    signal() //signal핸들러 등록 메소드
    alarm() // 알람 시그널을 발생시키는 메소드
    getpwnam() //사용자의 정보를 얻어오는 메소드
[Given]         :
    int signo // 시그널 번호
[Returns]       :
==================================================================*/

void
MyAlarmHandler(int signo)
{
	struct passwd	*rootptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	printf("in signal handler\n");

	if ((rootptr = getpwnam("root")) == NULL)  {
		perror("getpwnam");
		exit(1);
	}

	return;
}
/*===============================================================
[Program Name] : nonreent.c
[Description]  :
    - 이 프로그램은 getpwnam이 nonreent라는 즉 동시에 처리돼서는 안되는 메소드인걸 보여주는 프로그램이다.
	- cjs의 사용자의 정보를 읽다가 alarm이 발생하게 되면 root의 정보를 읽어서 저장하기 대문에 처음에 의도했던 cjs의 사용자의 정보가 넘어오지 않는다.
[Input]        :
[Output]       :
[Calls]        :
	signal() //signal핸들러 등록 메소드
    alarm() // 알람 시그널을 발생시키는 메소드
    getpwnam() //사용자의 정보를 얻어오는 메소드
[특기사항]     :
==================================================================*/
main()
{
	struct passwd	*ptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	for ( ; ; )  {
		if ((ptr = getpwnam("cjs")) == NULL)  {
			perror("getpwnam");
			exit(1);
		}

		if (strcmp(ptr->pw_name, "cjs") != 0)  {
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
