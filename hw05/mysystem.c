#include <stdio.h>
#include <stdlib.h>
#define	MAX_CMD		256
/*===============================================================
[Function Name] : mysystem(char *cmd)
[Description]   :
	- cmd를 받으면 system 함수처럼 cmd명령어를 fork exec waitpid 순서대로 하는 함수이다.
	- 먼저 execv함수를 이용하기 위해 벡터를 미리 선언을 해준다
	- fork를 통해 자식 프로세스를 만든뒤 자식 프로세스가 execv함수를 수행하도록한다.
	- 미리 작성된 프로그램(명령어)를 수행하기 위해서 execv의 path에 그 프로그램이 있는 path를 적어준다(argv에 sh -c를 넣은 이유는 system함수가 실제로 /bin/sh -c cmd를 수행하기 때문이다)
	- 그 다음 waitpid를 통해 프로세스가 끝나길 기다린다.(여기서 status를 받아서 나중에 끝나면 return 해준다. 만약 정상 처리 되면 0을 반환하게 된다)
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
	fork() // 자식 프로세스를 생성하는 함수
	execv() //벡터로 파라미터를 받아서 다른 프로그램을 실행시키는 함수
	waitpid // 특정 pid가 끝나길 기다리는 함수
[Given]         :
    char *cmd //수행할 명령어
[Returns]       :
	int status // 함수가 정상 종료되면 0을 반환
==================================================================*/
int mysystem(char *cmd){
    int pid;
    int status;
    char *argv[] = {"sh","-c",cmd,NULL};
    if((pid=fork())<0){
        perror("fork");
        return -1;
    }
    else if (pid==0){
        if(execv("/bin/sh",argv)<0){
            perror("execv");
            return -1;
        }
    }
    if (waitpid(pid,&status,0)<0){
        perror("waitpid");
        return -1;
    }
    return status;
}

/*===============================================================
[Program Name] : mysystem.c
[Description]  : 
    - 수행할 명령어를 입력으로 받아서 fgets를 통해 cmd로 저장한다
    - cmd가 q이면 종료하면 아니면 mysystem을 통해 명령어를 수행한다.
[Input]        :
[Output]       :
[Calls]        :            
    fgets() // 파일에서 문자열을 가져오는 함수
    mysystem() // 명령어를 수행하는 함수
[특기사항]     : 
==================================================================*/
main()
{
    int		status;
    char cmd[MAX_CMD];
    while (1)  {
        printf("CMD> ");
        fgets(cmd, MAX_CMD, stdin);
        if (cmd[0] == 'q')
            break;
        if((status=mysystem(cmd))<0){
            perror("mysystem");
            exit(1);
        }
        printf("status = %d\n",status);
    }
}