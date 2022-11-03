#include <stdio.h>
#include <unistd.h>
/*===============================================================
[Program Name] : myln.c
[Description]  :
	- 이 파일은 기존 파일을 하드링크해서 새로운 파일을 하나 만드는 파일이다.
	- link라는 함수를 통해 현재 파일과 새롭게 만들 파일을 파라미터로 넣어줘서 현재 파일에 새로운 파일을 하드 링크로 해서 생성한다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
    fprintf() // stderr에 뒤에 오는 내용을 출력한다
	link(char *existingpath, char *newpath) // 현재 파일을 하드링크해서 새로운파일을 만든다
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main(int argc, char *argv[])
{
    if (argc != 3)  {
        fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
        exit(1);
    }

    if (link(argv[1],argv[2]) < 0)  {
        perror("link");
        exit(1);
    }
}
