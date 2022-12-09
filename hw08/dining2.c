#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

#define	NUM_MEN		5
#define	NLOOPS		5

#define	LEFT(i)		((i+NUM_MEN-1)%NUM_MEN)
#define	RIGHT(i)	((i+1)%NUM_MEN)

enum  { THINKING, EATING, HUNGRY };

sem_t	Philosopher[NUM_MEN];
sem_t	Mutex;
int		State[NUM_MEN];
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
[Function Name] : Thinking(int id)
[Description]   :
    - 이 함수는 현재 철학자가 생각하고 있는걸 나타내는 함수이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    ThreadUsleep() // thread를 sleep 시키는 함수
[Given]         :
    int id // 철학자의 id값
[Returns]       :
=================================================================*/
void
Thinking(int id)
{
	printf("Philosopher%d: Thinking.....\n", id);
	ThreadUsleep((rand()%200)*10000);
	printf("Philosopher%d: Want to eat.....\n", id);
}
/*===============================================================
[Function Name] : Eating(int id)
[Description]   :
    - 이 함수는 현재 철학자가 먹고 있는걸 나타내는 함수이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    ThreadUsleep() // thread를 sleep 시키는 함수
[Given]         :
    int id // 철학자의 id값
[Returns]       :
=================================================================*/
void
Eating(int id)
{
	printf("Philosopher%d: Eating.....\n", id);
	ThreadUsleep((rand()%100)*10000);
}
/*===============================================================
[Function Name] : Test(int id)
[Description]   :
    - 이 함수는 현재 철학자가 배고픈 상태이고 밥을 먹을 수 있는지 체크하고 있으면 상태를 eating 상태로 바꾸고 철학자가 wait상태이면 깨우는 함수이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	sem_post() // 세마포어를 반납하는 함수 (+1 작업)
[Given]         :
    int id // 철학자의 id값
[Returns]       :
=================================================================*/
void
Test(int id)
{
	if (State[id] == HUNGRY && State[LEFT(id)] != EATING 
			&& State[RIGHT(id)] != EATING)  {
		State[id] = EATING;

		if (sem_post(&Philosopher[id]) < 0)  {
			perror("sem_post");
			pthread_exit(NULL);
		}
	}
}
/*===============================================================
[Function Name] : PickUp(int id)
[Description]   :
	- 철학자가 젓가락을 들려고 하는 함수이고 test를 통해 밥을 먹을 수 있는지(젓가락 두개를 다 사용할 수 있는지)확인하고 sem_wait을 통해 만약 철학자가 들 수 있는 상태면 밥을 먹기 시작하고 아니면 wait하면서 기다린다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	sem_wait() // 세마포어를 할당받는 함수(-1 작업) 
    sem_post() // 세마포어를 반납하는 함수 (+1 작업)
[Given]         :
    int id // 철학자의 id값
[Returns]       :
=================================================================*/
void
PickUp(int id)
{
	if (sem_wait(&Mutex) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}

	State[id] = HUNGRY;

	Test(id);

	if (sem_post(&Mutex) < 0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}

	if (sem_wait(&Philosopher[id]) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
}
/*===============================================================
[Function Name] : PutDown(int id)
[Description]   :
    - 철학자가 젓가락을 내려놓는 함수이고 mutex 세마포어가 사용중이면 기다렸다가 아니면 철학자의 상태를 생각중 상태로 바꾸고 오른쪽이나 왼쪽이 젓가락을 기다리는 상태인지 Test를 통해 확인하고 만약 그렇다면 깨워준다. 그 다음 mutex 세마포어를 post를 통해 반납한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    sem_wait() // 세마포어를 할당받는 함수(-1 작업) 
    sem_post() // 세마포어를 반납하는 함수 (+1 작업)
[Given]         :
    int id // 철학자의 id값
[Returns]       :
=================================================================*/
void
PutDown(int id)
{
	if (sem_wait(&Mutex) < 0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}

	State[id] = THINKING;

	Test(LEFT(id));
	Test(RIGHT(id));

	if (sem_post(&Mutex) < 0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}
}
/*===============================================================
[Function Name] : DiningPhilosopher(int* pId)
[Description]   :
    - 이 함수는 n명의 철학자가 한명씩 자신의 젓가락과 다음번째에 있는 젓>가락을 들어서 eating을 하고 다시 젓가락을 내려놓는걸 세마포어로 구현한 함
수이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    pthread_exit() // thread를 종료하는 함수
    Thinking() // 철학자가 생각하고 있는 걸 실행시키는 함수
    Eating() // 철학자가 밥먹고 있는 걸 실행시키는 함수
    PutDown() // 철학자가 젓가락을 내려놓는 함수
	PickUp() // 철학자가 젓가락을 집어드는 함수
[Given]         :
    int* pId // 철학자의 id값이 포함된 array
[Returns]       :
=================================================================*/
void
DiningPhilosopher(int *pId)
{
	int		i;
	int		id = *pId;

	for (i = 0 ; i < NLOOPS ; i++)  {

		Thinking(id);

		PickUp(id);

		Eating(id);

		PutDown(id);
	}

	printf("Philosopher%d: thinking & eating %d times.....\n", id, i);

	pthread_exit(NULL);
}
/*===============================================================
[Program Name] : dining2.c
[Description]  :
    - 이 프로그램은 밥먹는 철학자 문제를 thread와 posix 세마포어를 이용해
서 구현한 문제이다. 이 버전은 hold and wait을 제거했기  때문에 deadlock이 발생될 가능성이 없는 버전이다.
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
	pthread_t	tid[NUM_MEN];
	int			i, id[NUM_MEN];

	srand(0x8888);

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (sem_init(&Philosopher[i], 0, 0) < 0)  {
			perror("sem_init");
			exit(1);
		}
		id[i] = i;
	}
	if (sem_init(&Mutex, 0, 1) < 0)  {
		perror("sem_init");
		exit(1);
	}

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (pthread_create(&tid[i], NULL, (void *)DiningPhilosopher, 
				(void *)&id[i]) < 0)  {
			perror("pthread_create");
			exit(1);
		}
	}

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (pthread_join(tid[i], NULL) < 0)  {
			perror("pthread_join");
			exit(1);
		}
	}
	if (sem_destroy(&Mutex) < 0) {
		perror("sem destroy");
	}
	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (sem_destroy(&Philosopher[i]) < 0)  {
			perror("sem_destroy");
		}
	}
}
