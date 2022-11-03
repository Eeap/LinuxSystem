#include <stdio.h>
#include <unistd.h>
/*===============================================================
[Program Name] : myrm.c
[Description]  :
    - 이 파일은 입력받은 디렉토리를 삭제하는 파일이다
	- argv로 입력받은 해당 디렉토리를 rmdir함수를 통해 삭제한다
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
    fprintf() // stderr에 뒤에 오는 내용을 출력한다
    rmdir(char *pathname) //directory를 삭제하는 함수
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main(int argc, char *argv[])
{
    if (argc != 2)  {
        fprintf(stderr, "Usage: %s dirname\n", argv[0]);
        exit(1);
    }

    if (rmdir(argv[1]) < 0)  {
        perror("rmdir");
        exit(1);
    }
}
//
// Created by 김수민 on 2022/11/01.
//
