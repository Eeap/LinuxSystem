#include <stdio.h>
#include "semlib.h"

/*===============================================================
[Function Name] : semInit(key_t key)
[Description]   :
	- key를 입력받아서 semget이라는 함수를 통해 세마포어의 id값을 가져오는 함수. 만약 없으면 하나 새로 만든다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
	semget() // 세마포어의 id값을 가져오거나 새로 만드는 함수
[Given]         :
    key_t key // 세마포어의 key
[Returns]       :
	int semid // 세마포어의 id
==================================================================*/
int
semInit(key_t key)
{
    int     semid;

    if ((semid = semget(key, 1, 0600 | IPC_CREAT)) < 0)  {
		perror("semget");
        return -1;
    }

    return semid;
}
 /*===============================================================
[Function Name] : semInitValue(int semid, int value)
[Description]   :
    - 세마포어의 id와 value를 입력으로 받아서 semctl이라는 함수를 통해 세마포어의 value값을 설정한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    semctl() // 세마포어를 control하는 함수
[Given]         :
    int value // 세마포어의 value
	int semid // 세마포어의 id
[Returns]       :
    int semid // 세마포어의 id
==================================================================*/
int
semInitValue(int semid, int value)
{
    union semun {
            int     val;
    } semun;

    semun.val = value;
    if (semctl(semid, 0, SETVAL, semun) < 0)  {
		perror("semctl");
        return -1;
    }

    return semid;
}
  /*===============================================================
[Function Name] : semWait(int semid)
[Description]   :
	- 세마포어가 남아있으면 자원을 하나 쓰기 위한 함수. 즉 세마포어 -1 작업을 한다.
	- SEM_UNDO라는 플래그로 세마포어가 자원을 반납하지 않고 종료되는 상황을 방지한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    semop() // 세마포어의 operation 설정 하는 함수
[Given]         :
    int semid // 세마포어의 id
[Returns]       :
==================================================================*/
int
semWait(int semid)
{
    struct sembuf   semcmd;

    semcmd.sem_num = 0;
    semcmd.sem_op = -1;
    semcmd.sem_flg = SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }

    return 0;
}
  /*===============================================================
[Function Name] : semTryWait(int semid)
[Description]   :
    - 세마포어가 남아있으면 자원을 하나 쓰기 위한 함수 하지만 TryWait은 기다리지 않고 에러를 반환하고 마찬가지로 남아있을 경우 세마포어 -1 작업을 한다.
    - SEM_UNDO라는 플래그로 세마포어가 자원을 반납하지 않고 종료되는 상황을 방지한다. IPC_NOWAIT이라는 플래그는 앞에서 말한 것처럼 기다리지 않도록 하는 플래그이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    semop() // 세마포어의 operation 설정 하는 함수
[Given]         :
    int semid // 세마포어의 id
[Returns]       :
==================================================================*/
int
semTryWait(int semid)
{
    struct sembuf   semcmd;

    semcmd.sem_num = 0;
    semcmd.sem_op = -1;
    semcmd.sem_flg = IPC_NOWAIT | SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }

    return 0;
}
/*===============================================================
[Function Name] : semPost(int semid)
[Description]   :
    - 세마포어 자원을 쓰고 반납하기 위한 함수로 세마포어에 +1작업을 한다.
    - SEM_UNDO라는 플래그로 세마포어가 자원을 반납하지 않고 종료되는 상황을 방지한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    semop() // 세마포어의 operation 설정 하는 함수
[Given]         :
    int semid // 세마포어의 id
[Returns]       :
==================================================================*/
int
semPost(int semid)
{
    struct sembuf   semcmd;

    semcmd.sem_num = 0;
    semcmd.sem_op = 1;
    semcmd.sem_flg = SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }

    return 0;
}
 /*===============================================================
[Function Name] : semGetValue(int semid)
[Description]   :
    - 세마포어의 id를 입력으로 받아서 semctl이라는 함수를 통해 세마포어의 value값을 return한다
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    semctl() // 세마포어를 control하는 함수
[Given]         :
    int semid // 세마포어의 id
[Returns]       :
	int value // 세마포어의 value
==================================================================*/
int
semGetValue(int semid)
{
    union semun {
            int     val;
    } dummy;

    return semctl(semid, 0, GETVAL, dummy);
}
  /*===============================================================
[Function Name] : semDestroy(int semid)
[Description]   :
	- semctl라는 함수를 통해 세마포어를 삭제하는 함수
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    semctl() // 세마포어를 control하는 함수
[Given]         :
    int semid // 세마포어의 id
[Returns]       :
==================================================================*/
int
semDestroy(int semid)
{
    union semun {
            int     val;
    } dummy;

    if (semctl(semid, 0, IPC_RMID, dummy) < 0)  {
		perror("semctl");
        return -1;
    }
    close(semid);

    return 0;
}
