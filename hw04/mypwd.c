#include <stdio.h>
#include <unistd.h>

#define	MAX_BUF	256
/*===============================================================
[Program Name] : mypwd.c
[Description]  :
	- 이 파일은 pwd 커맨드와 동일한 작업을 하며 현재 dir위치를 출력하는 파일이다
	- getcwd함수를 통해 현재 디렉토리를 알아내서 buf에 저장하고 그 buf의 내용을 출력한다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
    getcwd() //현재 dir의 위치를 알려주는 함수
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main(int argc, char *argv[])
{
    char	buf[MAX_BUF];

    if (getcwd(buf,MAX_BUF)==NULL)  {
        perror("getcwd");
        exit(1);
    }

    printf("%s\n", buf);
}
