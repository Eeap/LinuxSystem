#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"

BoundedBufferType	Buf;
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
	- buf의 counter가 MAX_BUF에 도달하면 busy waiting을 하고 그렇지 않으면 버퍼에 데이터를 랜덤으로 생성해서 넣고 thread를 sleep하는 함수
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
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

	for (i = 0 ; i < NLOOPS ; i++)  {
		if (Buf.counter == MAX_BUF)  {
			printf("Producer: Buffer full. Waiting.....\n");
			while (Buf.counter == MAX_BUF)
				;
		}

		printf("Producer: Producing an item.....\n");
		data = (rand()%100)*10000;
		Buf.buf[Buf.in].data = data;
		Buf.in = (Buf.in + 1) % MAX_BUF;
		Buf.counter++;

		ThreadUsleep(data);
	}

	printf("Producer: Produced %d items.....\n", i);
	printf("Producer: %d items in buffer.....\n", Buf.counter);
	
	pthread_exit(NULL);
}
/*===============================================================
[Function Name] : Consumer(void *dummy)
[Description]   :
	- Buf의 카운터가 0이면 가져갈 데이터가 없기 때문에 busy waiting을 통해 기다리다가 데이터가 들어오면 데이터를 꺼내고 thread를 잠시 sleep시킨다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    rand() // random한 숫자를 만드는 함수
    ThreadUsleep() // thread를 sleep 시키는 함수
    pthread_exit() // thread를 exit 하는 함수
[Given]         :
    void *dummy // dummy pointer
[Returns]       :
==================================================================*/
void
Consumer(void *dummy)
{
	int		i, data;

	printf("Consumer: Start.....\n");

	for (i = 0 ; i < NLOOPS ; i++)  {
		if (Buf.counter == 0)  {
			printf("Consumer: Buffer empty. Waiting.....\n");
			while (Buf.counter == 0)
				;
		}

		printf("Consumer: Consuming an item.....\n");
		data = Buf.buf[Buf.out].data;
		Buf.out = (Buf.out + 1) % MAX_BUF;
		Buf.counter--;

		ThreadUsleep((rand()%100)*10000);
	}

	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer.....\n", Buf.counter);

	pthread_exit(NULL);
}
/*===============================================================
[Program Name] : prodcons_t.c
[Description]  :
	- 이 프로그램은 Producer 쓰레드와 Consumer 쓰레드를 하나씩 생성해 하나의 프로세스에서 쓰레드를 이용해서 버퍼에 데이터를 넣고 데이터를 빼는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
	- pthread_create() // thread를 생성하는 함수
	- pthread_join() // 특정 thread를 기다리는 함수
[특기사항]     :
==================================================================*/
main()
{
	pthread_t	tid1, tid2;

	srand(0x8888);

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

	printf("Main    : %d items in buffer.....\n", Buf.counter);
}

