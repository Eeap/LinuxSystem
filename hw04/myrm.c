#include <stdio.h>
/*===============================================================
[Program Name] : myrm.c
[Description]  :
    - 이 파일은 해당 파일을 삭제하는 파일이다
	- 입력으로 받은 argv[i]파일을 remove라는 함수를 이용해서 삭제한다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :            
    fprintf() // stderr에 뒤에 오는 내용을 출력한다
    remove(char *pathname) //해당 파일을 삭제한다
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     : 
===============================================================*/

main(int argc, char *argv[])
{
    int		i;

    if (argc == 1)  {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    for (i = 1 ; i < argc ; i++)  {
        if (remove(argv[i]) < 0)  {
            perror("remove");
            exit(1);
        }
    }
}