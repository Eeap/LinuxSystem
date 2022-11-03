#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*===============================================================
[Program Name] : fork.c
[Description]  : 
    - fork를 통해 현재 프로세스와 똑같은 프로세스를 하나 만든다
    - pid가 0일 경우 자식을 의미하고 0보다 클 경우 부모 프로세스를 의미한다
	- fork는 똑같은 메모리를 하나 더 복사하는 것이므로 독립적을 의미한다. 따라서 자식프로세스의 Var,var 값을 바꾸게 되면 부모 프로세스와 다르게 출력된다.
[Input]        :
[Output]       :
[Calls]        :            
	write() // 파일descriptor에 buf에 있는 값을 write하는 함수
    fork() // 현재 프로세스와 똑같은 프로세스를 하나 더 만드는 함수
    getpid() //process id 반환
    perror() // 에러메시지 출력
	sleep() //해당 시간만큼 프로세스를 재운다.
[특기사항]     : 
==================================================================*/
int		Var = 6;
char	Buf[] = "a write to stdout\n";

main()
{
    int		var;
    pid_t	pid;

    var = 88;
    write(STDOUT_FILENO, Buf, sizeof(Buf)-1);
    printf("Before fork\n");

    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        /* child */
        Var++;
        var++;
    }
    else  {
        /* parent */
        sleep(2);
    }

    printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
}