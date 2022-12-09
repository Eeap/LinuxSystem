#include <stdio.h>
#include <pthread.h>
#include "semlib2.h"

/*===============================================================
[Function Name] : sem_init(sem_t *sem, int pshared, int value)
[Description]   :
	- 이 함수는 세마포어를 초기화하는 함수로서 psahared가 0이 아니면 여러 프로세스에서 공유중이므로 에러를 출력하고 mutex lock과 condition variables를 초기화하고 세마포어의 value에 입력받은 value를 저장한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	pthread_cond_init() // condition variables를 초기화하는 함수
	pthread_mutex_init() // mutex를 초기화하는 함수
[Given]         :
    sem_t *sem // 세마포어 값
	int pshared // 현재 프로세스에서 사용중인지
	int value // 세마포어의 value
[Returns]       :
=================================================================*/
int
sem_init(sem_t *sem, int pshared, int value)
{
	if (pshared)  {
		fprintf(stderr, "Function not supported\n");
		return -1;
	}

	if (pthread_mutex_init(&sem->mutex, NULL) < 0)
		return -1;

	if (pthread_cond_init(&sem->cond, NULL) < 0)
		return -1;

	sem->sval = value;

	return 0;
}
/*===============================================================
[Function Name] : sem_wait(sem_t *sem)
[Description]   :
	- 이 함수는 세마포어를 하나 사용하는 함수로서 만약 세마포어가 남아있지 않다면 cond_wait을 써서 조건을 만족할때까지 기다리다가 만족되면 세마포어를 하나 사용한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	pthread_mutex_lock() // 뮤텍스 락을 거는 함수
    pthread_cond_wait() // 특정 condition이 만족할때까지 기다리는 함수
    pthread_mutex_unlock() // 뮤텍스 락을 반납하는 함수
[Given]         :
    sem_t *sem // 세마포어 값
[Returns]       :
=================================================================*/
int
sem_wait(sem_t *sem)
{
	if (pthread_mutex_lock(&sem->mutex) < 0)
		return -1;

	if (sem->sval == 0)  {
		while (sem->sval == 0)  {
			if (pthread_cond_wait(&sem->cond, &sem->mutex) < 0)  {
				if (pthread_mutex_unlock(&sem->mutex) < 0)
					return -1;
				return -1;
			}
		}
		sem->sval--;
	}
	else  {
		sem->sval--;
	}

	if (pthread_mutex_unlock(&sem->mutex) < 0)
		return -1;

	return 0;
}
/*===============================================================
[Function Name] : sem_trywait(sem_t *sem)
[Description]   :
    - 이 함수는 세마포어를 하나 사용하는 함수로서 만약 세마포어가 남아있지 않다면 mutex lock을 반납하고 fail처리한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    pthread_mutex_lock() // 뮤텍스 락을 거는 함수
    pthread_mutex_unlock() // 뮤텍스 락을 반납하는 함수
[Given]         :
    sem_t *sem // 세마포어 값
[Returns]       :
=================================================================*/
int
sem_trywait(sem_t *sem)
{
	if (pthread_mutex_lock(&sem->mutex) < 0)
		return -1;

	if (sem->sval == 0)  {
		if (pthread_mutex_unlock(&sem->mutex) < 0)
			return -1;
		return -1;
	}
	else  {
		sem->sval--;
	}

	if (pthread_mutex_unlock(&sem->mutex) < 0)
		return -1;

	return 0;
}
/*===============================================================
[Function Name] : sem_post(sem_t *sem)
[Description]   :
    - 이 함수는 세마포어를 하나 반납하는 함수로서 만약 세마포어가 남아있>지 않다면 cond_signal을 써서 조건을 wait하고 있는걸 깨워주고 mutex lock을 반납하며 남아있는 경우엔 하나 증가시키고 mutex lock을 반납한다
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    pthread_mutex_lock() // 뮤텍스 락을 거는 함수
    pthread_cond_signal() // 특정 condition을 wait하고 있는 걸 깨우는 함>수
    pthread_mutex_unlock() // 뮤텍스 락을 반납하는 함수
[Given]         :
    sem_t *sem // 세마포어 값
[Returns]       :
=================================================================*/
int
sem_post(sem_t *sem)
{
	if (pthread_mutex_lock(&sem->mutex) < 0)
		return -1;

	if (sem->sval == 0)  {
		if (pthread_cond_signal(&sem->cond) < 0)  {
			if (pthread_mutex_unlock(&sem->mutex) < 0)
				return -1;
			return -1;
		}
	}

	sem->sval++;

	if (pthread_mutex_unlock(&sem->mutex) < 0)
		return -1;

	return 0;
}
/*===============================================================
[Function Name] : sem_getvalue(sem_t *sem,int *sval)
[Description]   :
	- 세마포어의 value를 가져오는 함수
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
[Given]         :
    sem_t *sem // 세마포어 값
	int *sval // 세마포어의 value
[Returns]       :
=================================================================*/
int
sem_getvalue(sem_t *sem, int *sval)
{
	*sval = sem->sval;

	return 0;
}
/*===============================================================
[Function Name] : sem_destroy(sem_t *sem)
[Description]   :
	- 세마포어를 삭제하는 함수로서 mutex랑 condition variable을 삭제한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	pthread_cond_destroy() // condition variables를 삭제하는 함수
    pthread_mutex_destroy() // mutex를 삭제하는 함수
[Given]         :
    sem_t *sem // 세마포어 값
[Returns]       :
=================================================================*/
int
sem_destroy(sem_t *sem)
{
	if (pthread_mutex_destroy(&sem->mutex) < 0)
		return -1;

	if (pthread_cond_destroy(&sem->cond) < 0)
		return -1;

	return 0;
}
