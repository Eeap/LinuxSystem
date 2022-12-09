#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"
/*
mutex와 condition variables를 이용하는 동기화 방식은 semaphore를 이용했을때와 구현상의  달리 별 차이가 없지만 세마포어는 시스템 범위에 걸쳐서 파일 시스템으로 관리되고 mutex는 프로세스의 범위를 가져서 프로세스가 종료될 때 자동으로 종료된다. 즉 세마포어는 다른 프로세스에서도 삭제가 가능하지만 mutex는 아니다.
*/

BoundedBufferType	Buf;
pthread_cond_t		NotFull;
pthread_cond_t		NotEmpty;
pthread_mutex_t		Mutex;
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
    - mutex lock 과 condition variables을 이용해서 버퍼에 데이터를 넣는 producing하는 함수
    - mutex lock을 통해 critical section에 진입하고 만약 buf의 counter가 1이면 condition variable을 이용해서 조건에 만족할때까지 wait을 한다. 그 다음 꽉차있지 않다면 데이터를 producing하고 notempty이라는 조건으로 기다리는 condition variable을 깨우고 mutex lock을 반납한다.

[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    pthread_mutex_lock() // 뮤텍스 락을 거는 함수
    pthread_cond_wait() // 특정 condition이 만족할때까지 기다리는 함수
    pthread_cond_signal() // 특정 condition을 wait하고 있는 걸 깨우는 함수
    pthread_mutex_unlock() // 뮤텍스 락을 반납하는 함수
    pthread_exit() // thread를 exit 하는 함수
[Given]         :
    void *dummy // dummy pointer
[Returns]       :
=================================================================*/
void
Producer(void *dummy)
{
	int		i, data;

	printf("Producer: Start.....\n");
	
	if (pthread_mutex_lock(&Mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	while (Buf.counter == 1)  {
		if (pthread_cond_wait(&NotFull, &Mutex) < 0)  {
			perror("pthread_cond_wait");
			pthread_exit(NULL);
		}
	}

	data = getpid();
	Buf.buf[0].data = data;
	Buf.counter++;
	printf("Producer: send data.....%d\n",data);
	if (pthread_cond_signal(&NotEmpty) < 0)  {
		perror("pthread_cond_signal");
		pthread_exit(NULL);
	}
	if (pthread_mutex_unlock(&Mutex) < 0)  {
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}

	ThreadUsleep(data);
	pthread_exit(NULL);
}
/*===============================================================
[Function Name] : Consumer(void *dummy)
[Description]   :
	- mutex lock 과 condition variables을 이용해서 버퍼에 있는 데이터를 consuming하는 함수
	- mutex lock을 통해 critical section에 진입하고 만약 buf의 counter가 0이면 condition variable을 이용해서 조건에 만족할때까지 wait을 한다. 그 다음 비어있지 않다면 데이터를 consuming하고 notfull이라는 조건으로 기다리는 condition variable을 깨우고 mutex lock을 반납한다.

[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	pthread_mutex_lock() // 뮤텍스 락을 거는 함수
    pthread_cond_wait() // 특정 condition이 만족할때까지 기다리는 함수
    pthread_cond_signal() // 특정 condition을 wait하고 있는 걸 깨우는 함수
    pthread_mutex_unlock() // 뮤텍스 락을 반납하는 함수
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

	if (pthread_mutex_lock(&Mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}

	while (Buf.counter == 0)  {
		if (pthread_cond_wait(&NotEmpty, &Mutex) < 0)  {
			perror("pthread_cond_wait");
			pthread_exit(NULL);
		}
	}

	data = Buf.buf[0].data;
	printf("Consumer: data receive : %d\n",data);
	Buf.counter--;

	if (pthread_cond_signal(&NotFull) < 0)  {
		perror("pthread_cond_signal");
		pthread_exit(NULL);
	}
	if (pthread_mutex_unlock(&Mutex) < 0)  {
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}

	ThreadUsleep(data);
	pthread_exit(NULL);
}
/*===============================================================
[Program Name] : sipc_t_m.c
[Description]  :
	- 이 프로그램은 producer와 consumer를 thread와 mutex lock, condition variables을 이용해서 sync를 구현한 프로그램이다
	- init을 통해 각각의 condition variables와 mutex lock을 초기화하고 다 쓰면 반납한다
	- thread를 create를 통해 만들고join으로 thread가 끝나길 기다린다.
[Input]        :
[Output]       :
[Calls]        :
    - pthread_cond_init() // condition variables를 초기화하는 함수
	- pthread_mutex_init() // mutex를 초기화하는 함수
	- pthread_cond_destroy() // condition variables를 삭제하는 함수
    - pthread_mutex_destroy() // mutex를 삭제하는 함수
	- pthread_create() // thread를 생성하는 함수
    - pthread_join() // 특정 thread를 기다리는 함수
[특기사항]     :
==================================================================*/
main()
{
	pthread_t	tid1, tid2;

	srand(0x8888);

	if (pthread_cond_init(&NotFull, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_cond_init(&NotEmpty, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&Mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
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

	if (pthread_cond_destroy(&NotFull) < 0)  {
		perror("pthread_cond_destroy");
	}
	if (pthread_cond_destroy(&NotEmpty) < 0)  {
		perror("pthread_cond_destroy");
	}
	if (pthread_mutex_destroy(&Mutex) < 0)  {
		perror("pthread_mutex_destroy");
	}
}
