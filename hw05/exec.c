#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*===============================================================
[Program Name] : exec.c
[Description]  : 
	- 코드 안에서 다른곳에 있는 프로그램을 실행시키는 파일이다. 
	- 먼저 fork를 통해 다른곳에 있는 프로그램을 실행시키기 위한 프로세스를 만들고 부모 프로세스는 waitpid 통해 기다린다
	- execl함수를 통해 해당 path에 있는 list로 입력을 받은 파일을 실행시킨다(마지막엔 끝을 알리기 위해 널을 넣어줘야한다)
	- 그 다음 마찬가지로 fork로 자식 프로세스를 만들고 이번엔 벡터로 파라미터를 받아서 실행하는 함수인 execv를 이용해서 해당 path에 있는 vector에 들어있는 파일을 실행시킨다. 여기도 마찬가지로 마지막엔 널값이 들어가야한다.
	- 그 다음에도 마찬가지로 fork로 자식 프로세스를 만들고 이번엔 execlp라는 함수를 통해 이 함수는 PATH라는 환경 변수에 등록된 디렉토리를 참고하여 프로그램을 실행해 주는데 첫번째 파라미터에 pathname이 아니라 filename을 준다. 
[Input]        :
[Output]       :
[Calls]        :            
	waitpid() //특정 pid가 끝나길 기다리는 함수
	execl() // list형식으로 받은 프로그램을 실행시키는 함수
	execv() //vector형식으로 받은 프로그램을 실행시키는 함수
	execlp() //PATH에 등록된 디렉토리를 참고하여 다른 프로그램을 실행시키는 함수
    fork() //현재 프로세스와 똑같은 프로세스를 만드는 함수
[특기사항]     : 
==================================================================*/
main()
{
    pid_t	pid;
    char	*argv[] = { "mycp", "exec.c", "exec2.c", NULL };

    // execl
    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        // mycp exec.c exec2.c
        if (execl("/home/cjs/lsp/file-io/mycp","mycp","exec.c","exec2.c",NULL)<0)  {
            perror("execl");
            exit(1);
        }
    }
    if (waitpid(pid, NULL, 0) < 0)  {
        perror("waitpid");
        exit(1);
    }

    // execv
    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        // mycp exec.c exec2.c
        if (execv("/home/cjs/lsp/file-io/mycp",argv)<0)  {
            perror("execv");
            exit(1);
        }
    }
    if (waitpid(pid, NULL, 0) < 0)  {
        perror("waitpid");
        exit(1);
    }

    // execlp
    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)  {
        // execute 'env' from PATH
        if (execlp("env","env",NULL)<0)  {
            perror("execlp");
            exit(1);
        }
    }
    if (waitpid(pid, NULL, 0) < 0)  {
        perror("waitpid");
        exit(1);
    }
}