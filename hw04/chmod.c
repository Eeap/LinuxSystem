#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
/*===============================================================
[Program Name] : chmod.c
[Description]  :
    - 이 파일은 bar와 foo라는 파일을 권한을 바꾸는 파일이다
	- stat을 통해 statbuf에 파일의 status를 가져온다
	- chmod를 이용해서 bar라는 파일의 group의 w권한을 끄고 uid를 비트를 키는데 이걸 키면 effective uid가 나중에 파일의 소유자 id로 되어서 해당 파일에 접근할 수 있다.
	- chmod를 이용해서 foo라는 파일의 user의 rw권한과 group의 r권한, other의 r권한을 킨다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
    stat(char *pathname, struct stat *buf) //파일의 status를 buf에 불러온다
	chmod(char *pathname, mode_t mode) //파일의 권한을 mode에 있는 값으로 바꾼다
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main()
{
    struct stat	statbuf;

    if (stat("bar", &statbuf) < 0)  {
        perror("stat");
        exit(1);
    }

    if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0)  {
        perror("chmod");
        exit(1);
    }

    /* S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH : ON */
    if (chmod("foo",S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))  {
        perror("chmod");
        exit(1);
    }
}
