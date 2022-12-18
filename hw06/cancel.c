#include <stdio.h>
#include <signal.h>
#include <pthread.h>

pthread_t	ThreadId[2];
/*===============================================================
[Function Name] : SigIntHandler(int signo)
[Description]   :
    - SIGINT라는 시그널이 오면 문자열을 출력하고 쓰레드를 다 종료시키고 종료하는 함수이다
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	- pthread_cancel() //thread를 cancel하는 메소드
	- pthread_join() //thread의 종료를 기다리는 메소드
    - exit() //시스템 종료 메소드
[Given]         :
    int signo //signal 번호
[Returns]       :
==================================================================*/
void
SigIntHandler(int signo)
{
	int		i;

	printf("Received a SIGINT signal by thread %d\n", pthread_self());
	printf("Terminate other threads: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	for (i = 0 ; i < 2 ; i++)  {
		if (pthread_cancel(ThreadId[i]))  {
			perror("pthread_cancel");
			exit(1);
		}
	}
	for (i = 0 ; i < 2 ; i++)  {
		if (pthread_join(ThreadId[i], NULL))  {
			perror("pthread_join");
			exit(1);
		}
	}
	printf("Threads terminated: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	exit(0);
}
/*===============================================================
[Function Name] : Thread1(void *dummy)
[Description]   :
	- thread를 다른사람이 종료할 수 있게 setcancelstate로 설정하고 setcanceltype을 통해 thread를 async로 해서 바로 종료하도록 설정을 한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	- pthread_setcancelstate() // thread의 cancel state옵션 설정 메소드
	- pthread_setcanceltype() // thread의 cancel type 옵션 설정 메소드
	- pthread_exit() // thread를 종료시키는 메소드
[Given]         :
    void *dummy // 여기선 NULL을 입력받음
[Returns]       :
==================================================================*/
void
Thread1(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
		;
}
/*===============================================================
[Function Name] : Thread2(void *dummy)
[Description]   :
    - thread를 다른사람이 종료할 수 있게 setcancelstate로 설정하고 setcanceltype을 통해 thread를 async로 해서 바로 종료하도록 설정을 한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	- pthread_exit() // thread를 종료시키는 메소드
    - pthread_setcancelstate() // thread의 cancel state옵션 설정 메소드
    - pthread_setcanceltype() // thread의 cancel type 옵션 설정 메소드
[Given]         :
    void *dummy // 여기선 NULL을 입력받음
[Returns]       :
==================================================================*/
void
Thread2(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
		;
}
/*===============================================================
[Program Name] : cancel.c
[Description]  :
    - 이 프로그램은 sigint라는 종료하는 ctrl+c 커맨드를 받으면 종료하는 프로그램이다.
	- thread를 두개를 만들어서 각각의 thread의 cancel 옵션을 설정해주고 핸들러 함수에서 쓰레드가 잘 cancel되는지 동작을 확인하는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
	- pthread_create() // thread를 만드는 메소드
    - signal() //signal 핸들러 등록 메소드
    - pause() // signal을 기다리는 메소
[특기사항]     :
==================================================================*/
main()
{
	if (pthread_create(&ThreadId[0], NULL, (void *)Thread1, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&ThreadId[1], NULL, (void *)Thread2, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	signal(SIGINT, SigIntHandler);

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
