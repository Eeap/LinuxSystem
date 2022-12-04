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
