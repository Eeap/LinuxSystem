#include <stdio.h>
#include <stdlib.h>
/*===============================================================
[Program Name] : system.c
[Description]  : 
	- system이라는 함수는 command에서 치던걸 넘겨주면 자식 프로세스를 알아서 fork로 만들고 exec이랑 waitpid도 다 알아서 하게 된다.

[Input]        :
[Output]       :
[Calls]        :            
	perror() // 에러 메시지 출력하는 함수
	system() //파라미터로 커맨드에서 치던걸 받으면 알아서 실행해주는 함수
[특기사항]     : 
==================================================================*/
main()
{
    int		status;

    if ((status = system("date")) < 0)  {
        perror("system");
        exit(1);
    }
    printf("exit status = %d\n", status);

    if ((status = system("nosuchcommand")) < 0)  {
        perror("system");
        exit(1);
    }
    printf("exit status = %d\n", status);

    /* $ who; exit 44 */
    if ((status=system("who; exit 44"))<0)  {
        perror("system");
        exit(1);
    }
    printf("exit status = %d\n", status);
}