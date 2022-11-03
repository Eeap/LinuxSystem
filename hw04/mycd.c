#include <stdio.h>
#include <unistd.h>
/*===============================================================
[Program Name] : mycd.c
[Description]  :
	- 이 파일은 cd 커맨드 작업과 동일한 작업을 하는 파일이며 현재 dir 위치를 바꾸는 파일이다.
	- chdir함수를 통해 파라미터로 받은 디렉토리로 dir위치를 옮긴다.
	- 하지만 이 함수를 실행하면 실제 cd커맨드와는 다르게 dir위치가 바뀌지 않는데 그 이유는 이 함수가 child process에서 실행되고 종료되기 때문에 현재 프로세스에는 바뀌지 않는 상태가 된다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
	fprintf() // stderr에 뒤에 오는 내용을 출력한다
    chdir() //해당 dir로 dir를 변경하는 함수
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main(int argc, char *argv[])
{
    if (argc != 2)  {
        fprintf(stderr, "Usage: %s dirname\n", argv[0]);
        exit(1);
    }

    if (chdir(argv[1]) < 0)  {
        perror("chdir");
        exit(1);
    }
}
