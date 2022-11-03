#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*===============================================================
[Function Name] : CharAtaTime(char *str)
[Description]   : string을 받으면 stdout buffer를 통해 string을 char로 하나씩 출력하는 함수이다
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
[Program Name] : race.c
[Description]  : 
	- fork를 통해 자식 프로세스를 만드는데 부모 프로세스와 자식 프로세스 둘다 CharAtaTime 함수를 이용해서 문자열을 출력하는데 for문을 통해 큰수로 반복하고 출력하다보니 글자가 겹치게 되고 출력하는 문자열이 무엇인지 모르게 되는 문제가 발생한다.
[Input]        :
[Output]       :
[Calls]        :            
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
        CharAtaTime("output from parent\n");
    }
}