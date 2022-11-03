#include <stdio.h>
/*===============================================================
[Program Name] : mymv.c
[Description]  :
    - 이 파일은 해당 파일의 이름을 바꾸거나 다른 곳으로 옮긴다.
    - 입력으로 받은 argv[1]를 argv[2]로 rename  함수를 이용해서 이름을 바꾸거나 파일을 옮긴다
	- 현재 디렉토리에 있는 걸 다른 디렉토리로 옮기는건 가능하지만 다른 디렉토리에 있는걸 현재 디렉토리로 옮기는건 안된다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
	rename(char *oldname, chaar *newname) // 파일의 이름을 바꾸거나 다른 곳으로 옮긴다
    fprintf() // stderr에 뒤에 오는 내용을 출력한다
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main(int argc, char *argv[])
{
    if (argc != 3)  {
        fprintf(stderr, "Usage: %s old new\n", argv[0]);
        exit(1);
    }

    if (rename(argv[1],argv[2])< 0)  {
        perror("rename");
        exit(1);
    }
}
