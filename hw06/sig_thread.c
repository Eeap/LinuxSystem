#include <stdio.h>
#include <signal.h>
#include <pthread.h>

#define	THREAD_MAIN
/*
#define	THREAD_1
#define	THREAD_2
*/

/*===============================================================
[Function Name] : SigIntHandler(int signo)
[Description]   :
    - SIGINT라는 시그널이 오면 문자열을 출력하고 종료하하는 함수이다
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    - exit() //시스템 종료 메소드
[Given]         :
    int signo //signal 번호
[Returns]       :
==================================================================*/
void
SigIntHandler(int signo)
{
	printf("Received a SIGINT signal by thread %d\n", pthread_self());
	printf("Terminate this process\n");

	exit(0);
}
/*===============================================================
[Function Name] : Thread1(void *dummy)
[Description]   :
    - 만약 define이 THREAD_1이면 SIGINT 시그널의 핸들러를 signal함수를 통해 등록하고 while문을 반복한다.
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
	signal() //signal 핸들러 등록 메소드
[Given]         :
    void *dummy // 여기선 NULL을 입력받음
[Returns]       :
==================================================================*/
void
Thread1(void *dummy)
{
#ifdef	THREAD_1
	signal(SIGINT, SigIntHandler);
#endif

	while (1)
		;
}
/*===============================================================
[Function Name] : Thread2(void *dummy)
[Description]   :
    - 만약 define이 THREAD_2이면 SIGINT 시그널의 핸들러를 signal함수를 통해 등록하고 while문>을 반복한다.
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
    signal() //signal 핸들러 등록 메소드
[Given]         :
    void *dummy // 여기선 NULL을 입력받음
[Returns]       :
==================================================================*/
void
Thread2(void *dummy)
{
#ifdef	THREAD_2
	signal(SIGINT, SigIntHandler);
#endif

	while (1)
		;
}
/*===============================================================
[Program Name] : sig_thread.c
[Description]  :
    - 이 프로그램은 thread를 두개를 만들어서 각각이 define에 따라 시그널을 등록하도록 쓰래ㅔ드를 만든다.
	- thread의 메인일 경우엔 메인 함수 내에서 시그널을 등록하고 for문안에서 pause를 통해 SIGINT 시그널을 기다린다.

[Input]        :
[Output]       :
[Calls]        :
	- pthread_create() //쓰레드 생성 메소드
    - signal() //signal 핸들러 등록 메소드
    - pause() // signal을 기다리는 메소
[특기사항]     :
==================================================================*/
main()
{

	pthread_t	tid1, tid2;

	if (pthread_create(&tid1, NULL, (void *)Thread1, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&tid2, NULL, (void *)Thread2, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	printf("Create two threads: tid1=%d, tid2=%d\n", tid1, tid2);
	printf("Main thread: tid=%d\n", pthread_self());

#ifdef	THREAD_MAIN
	signal(SIGINT, SigIntHandler);
#endif

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
