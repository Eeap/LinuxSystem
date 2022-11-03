#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
/*===============================================================
[Program Name] : myls.c
[Description]  :
    - 이 파일은 ls 커맨드와 똑같은 작업을 수행하는 파일로 현재 디렉토리에 있는 파일과 디렉토리를 출력하는 파일이다.
    - opendir로 현재 디렉토리를 열고 readdir로 opendir를 통해 반환하는 DIR 포인터를 파라미터로 받아서 dirent 구조체로 받아서 읽고 d_name을 출력한다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
    opendir(char *pathname) // 디렉토리를 열고 DIR 포인터를 반환한다
	readdir(DIR *dp) //opendir로 반환하는 DIR 포인터를 파라미터로 받아서 디렉토리에 있는 파일이나 디렉토리들을 하나씩 읽는다
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main()
{
    DIR				*dp;
    struct dirent	*dep;

    if ((dp = opendir(".")) == NULL)  {
        perror("opendir");
        exit(0);
    }

    while (dep=readdir(dp))  {
        printf("%s\n", dep->d_name);
    }

    closedir(dp);
}
