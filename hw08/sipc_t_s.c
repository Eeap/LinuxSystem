#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"

/*
semaphore를 이용하는 동기화 방식은 mutex와 condition variables를 이용했을 때와 구현상의  달리 별 차이가 없지만 세마포어는 시스템 범위에 걸쳐서 파일 시스템으로 관리되고 mutex는 프로세스의 범위를 가져서 프로세스가 종료될 때 자동으로 종료된다. 즉 세마포어는 다른 프로세스에서도 삭제가 가능하지만 mutex는 아니다.
*/

BoundedBufferType	Buf;
sem_t				EmptySem, FullSem, MutexSem;
/*===============================================================
[Function Name] : ThreadUsleep(int usecs)
[Description]   :
    - thread를 condition variable을 이용해서 usecs만큼 sleep 시키는 함수
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    pthread_cond_init() // condition variables을 초기화하는 함수
    pthread_mutex_init() // mutex lock을 초기화하는 함수
    pthread_mutex_lock() // mutex를 lock하는 함수
    pthread_cond_timedwait() // 특정 시간의 condition을 기다리는 함수
    pthread_mutex_destroy() // mutex를 삭제하는 함수
    pthread_cond_destroy() //condition variables을 삭제하는 함수
    gettimeofday() // 현재 시간을 가져오는 함수
    pthread_exit() // thread를 종료하는 함수
[Given]         :
    int usecs // 마이크초 단위 시간
[Returns]       :
==================================================================*/

void
ThreadUsleep(int usecs)
{
	pthread_cond_t		cond;
	pthread_mutex_t		mutex;
	struct timespec		ts;
	struct timeval		tv;

	if (pthread_cond_init(&cond, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	if (ts.tv_nsec >= 1000000000)  {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	if (pthread_mutex_lock(&mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  {
		perror("pthread_cond_timedwait");
		pthread_exit(NULL);
	}

	if (pthread_cond_destroy(&cond) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&mutex) < 0)  {
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}
}
/*===============================================================
[Function Name] : Producer(void *dummy)
[Description]   :
	- sem_wait 이라는 시스템 콜을 통해 먼저 비어있는게 있는지 확인하고(없으면 기다림) 이제 buf라는 critical section에 진입하기 전에 mutex 세마포어를 사용해서 접근하는데 만약 mutex세마포어가 사용중이면 기다렸다가 값이 1이 됐을때 -1하고 buf에 데이터에 저장한다.
	- 그 다음 sem_post를 통해 mutex 세마포어를 반납하고 full세마포어를 하나 추가한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	sem_wait() // 세마포어를 할당받는 함수(-1 작업)
	sem_post() // 세마포어를 반납하는 함수 (+1 작업)
	rand() // random한 숫자를 만드는 함수
	ThreadUsleep() // thread를 sleep 시키는 함수
	pthread_exit() // thread를 exit 하는 함수
[Given]         :
    void *dummy // dummy pointer
[Returns]       :
==================================================================*/
void
Producer(void *dummy)
{
	int		i, data;

	printf("Producer: Start.....\n");

	if (sem_wait(&EmptySem) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	if (sem_wait(&MutexSem) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	data = getpid();
	Buf.buf[0].data = data;
	Buf.counter++;
	printf("Producer: send data.....%d\n",data);
	if (sem_post(&MutexSem) < 0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}
	if (sem_post(&FullSem) < 0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}

	ThreadUsleep(data);
	pthread_exit(NULL);
}
/*===============================================================
[Function Name] : Consumer(void *dummy)
[Description]   :
	- sem_wait 이라는 시스템 콜을 통해 먼저 full세마포어가  있는지 확인하고(없으면 기다림) 이제 buf라는 critical section에 진입하기 전에 mutex 세마포어를 사용해서 접근하는데 만약 mutex 세마포어가 사용중이면 기다렸다가 값이 1이 됐을때 -1하고 buf에서 데이터를 가져온다.
    - 그 다음 sem_post를 통해 mutex 세마포어를 반납하고 empty세마포어를 하나 추가한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	sem_wait() // 세마포어를 할당받는 함수(-1 작업)
    sem_post() // 세마포어를 반납하는 함수 (+1 작업)
    rand() // random한 숫자를 만드는 함수
    ThreadUsleep() // thread를 sleep 시키는 함수
    pthread_exit() // thread를 exit 하는 함수
[Given]         :
    void *dummy // dummy pointer
[Returns]       :
=================================================================*/
void
Consumer(void *dummy)
{
	int		i, data;

	printf("Consumer: Start.....\n");

	if (sem_wait(&FullSem) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	if (sem_wait(&MutexSem) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	data = Buf.buf[0].data;
	printf("Consumer: data receive : %d\n",data);
	Buf.counter--;
	if (sem_post(&MutexSem) < 0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}
	if (sem_post(&EmptySem) < 0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}

	ThreadUsleep((rand()%100)*10000);

	pthread_exit(NULL);
}
/*===============================================================
[Program Name] : sipc_t_s.c
[Description]  :
	- 이 프로그램은 Producer 쓰레드와 Consumer 쓰레드를 하나씩 생성해 하나의 프로세스에서 쓰레드를 이용해서 버퍼에 데이터를 넣고 데이터를 빼는 프로그램이다.
	- 먼저 empty세마포어와 full세마포어, mutex세마포어를 초기화한다. 그 다음 thread를 create하고 join으로 기다린다. 다 끝나면 세마포어를 destroy해준다.
[Input]        :
[Output]       :
[Calls]        :
	- sem_init() // 세마포어를 초기화하는 함수
	- sem_destroy() // 세마포어를 삭제하는 함수
	- pthread_create() // thread를 생성하는 함수
	- pthread_join() // 특정 thread를 기다리는 함수
[특기사항]     :
==================================================================*/
main()
{
	pthread_t	tid1, tid2;

	srand(0x9999);

	if (sem_init(&EmptySem, 0, 1) < 0)  {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(&FullSem, 0, 0) < 0)  {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(&MutexSem, 0, 1) < 0)  {
		perror("sem_init");
		exit(1);
	}

	if (pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_join(tid1, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}

	if (sem_destroy(&EmptySem) < 0)  {
		perror("sem_destroy");
	}
	if (sem_destroy(&FullSem) < 0)  {
		perror("sem_destroy");
	}
	if (sem_destroy(&MutexSem) < 0)  {
		perror("sem_destroy");
	}
}
