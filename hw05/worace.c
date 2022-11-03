#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
/*===============================================================
[Function Name] : CharAtaTime(char *str)
[Description]   : string을 받으면 stdout buffer를 통해 string을 char로 하나씩 출력하>는 함수이다
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
    setbuf() //buf설정
    putc() // 첫번째 파라미터 buf에 출력
[Given]         :
    char *str //출력할 문자열
[Returns]       :
==================================================================*/
void
CharAtaTime(char *str)
{
    char	*ptr;
    int		c, i;

    setbuf(stdout, NULL);
    for (ptr = str ; c = *ptr++ ; )  {
        for(i = 0 ; i < 999999 ; i++)
            ;
        putc(c, stdout);
    }
}
/*===============================================================
[Program Name] : worace.c
[Description]  : 
	- fork를 통해 자식 프로세스를 만들게 되는데 race condition을 피하기 위해 부모 프로세스는 wait을 통해 자식 프로세스가 문자열의 출력을 마칠때까지 기다렸다가 출력한다.
[Input]        :
[Output]       :
[Calls]        :   
	wait() //자식 프로세스가 끝날떄까지 기다리는 함수         
    fork() //현재 프로세스와 똑같은 프로세스를 만드는 함수
    CharAtaTime() /문자열을 한글자씩 출력하는 함수
[특기사항]     : 
==================================================================*/
main()
{
    pid_t	pid;


    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        CharAtaTime("output from child\n");
    }
    else  {
        wait(NULL);
        CharAtaTime("output from parent\n");
    }
}