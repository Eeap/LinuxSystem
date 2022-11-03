#include <stdio.h>
#include <pthread.h>

#define	MAX_CMD		256
/*===============================================================
[Function Name] : DoCmd(char *cmd)
[Description]   : cmd를 받으면 실제로 그 명령을 수행하진 않고 수행했다는 표시만 print
f를 하는 함수이다. 마지막으로 출력을 다한뒤에는 thread를 종료시킨다.
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
	pthread_exit() //thread를 종료하는 함수
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

    pthread_exit(NULL);
}
/*===============================================================
[Program Name] : cmd_t.c
[Description]  : 
    - 수행할 명령어를 입력으로 받아서 fgets를 통해 cmd로 저장한다
    - cmd가 q이면 종료하면 아니면 pthread_create를 통해 tid값을 가지는 thread를 하나 만들고 DoCmd를 수행한다.
	- pthread_join을 통해 해당 쓰레드가 끝날때까지 기다린다.
[Input]        :
[Output]       :
[Calls]        :            
    fgets() // 파일에서 문자열을 가져오는 함수
    DoCmd() // 명령어를 수행하는 함수
	pthread_create() //thread를 생성하는 함수
	pthread_join() //thread가 끝날떄까지 기다리는 함수
[특기사항]     : 
==================================================================*/
main()
{
    char		cmd[MAX_CMD];
    pthread_t	tid;

    while (1)  {
        printf("CMD> ");
        fgets(cmd, MAX_CMD, stdin);
        if (cmd[0] == 'q')
            break;

        if (pthread_create(&tid,NULL,(void *)DoCmd,(void *)cmd)<0)  {
            perror("pthread_create");
            exit(1);
        }

#if 0
        pthread_join(tid, NULL);
#endif
    }
}