#include <stdio.h>

#define	MAX_CMD		256
/*===============================================================
[Function Name] : DoCmd(char *cmd)
[Description]   : cmd를 받으면 실제로 그 명령을 수행하진 않고 수행했다는 표시만 print
f를 하는 함수이다.
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
[Given]         :
    char *cmd //수행할 명령어
[Returns]       :
==================================================================*/
void
DoCmd(char *cmd)
{
    printf("Doing %s", cmd);
    sleep(1);
    printf("Done\n");
}
/*===============================================================
[Program Name] : cmd_p.c
[Description]  : 
    - 수행할 명령어를 입력으로 받아서 fgets를 통해 cmd로 저장한다
    - cmd가 q이면 종료하면 아니면 fork를 통해 자식 프로세스를 만들고 자식프로세스가 DoCmd를 통해 명령어를 수행한다.
[Input]        :
[Output]       :
[Calls]        :            
    fgets() // 파일에서 문자열을 가져오는 함수
    DoCmd() // 명령어를 수행하는 함수
	fork() // 자식 프로세스를 만드는 함수
	wait() // 자식 프로세스 중 하나가 끝나길 기다리는 함수
[특기사항]     : 
==================================================================*/
main()
{
    char	cmd[MAX_CMD];
    int		pid;

    while (1)  {
        printf("CMD> ");
        fgets(cmd, MAX_CMD, stdin);
        if (cmd[0] == 'q')
            break;

        if ((pid=fork())<0)  {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)  {
            DoCmd(cmd);
            exit(0);
        }
#if 0
        else  {
			wait(NULL);
		}
#endif
    }
}