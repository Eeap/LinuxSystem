#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
/*===============================================================
[Program Name] : mymd.c
[Description]  :
    - 이 파일은 입력으로 받은 이름으로 디렉토리를 755(user rwx, group rx, other rx)권한으로 만드는 파일이다
	-
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
    fprintf() // stderr에 뒤에 오는 내용을 출력한다
    mkdir(char *pathname, mode_t mode) //directory를 새로 만드는 함수
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/

main(int argc, char *argv[])
{
    if (argc != 2)  {
        fprintf(stderr, "Usage: %s dirname\n", argv[0]);
        exit(1);
    }

    /* 755 permission */
    if (mkdir(argv[1], 0755) < 0)  {
        perror("mkdir");
        exit(1);
    }
}
