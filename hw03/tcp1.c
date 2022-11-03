#include <stdio.h>
/*===============================================================
[Program Name] : tcp1.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 text로 read하고 반환받은 포인터를 src에 저장
	- argv[2]으로 받은 파일을 fopen해서 text로 write하고 반환받은 포인터를 dst에저장
	- fopen시 반환 값이 NULL이면 에러메시지를 출력하고 종료한다 

	- fgetc()를 통해 src에 있는 텍스트를 파일의 끝에 도달할 때 까지 한글자씩 받아서 ch에 저장하고 그것을 fputc()를 통해 dst에 저장한다.
	- src에 있는 텍스트를 dst에 다 저장했으면 끝낸다.
    - fclose를 통해 파일을 닫는다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오
픈하고 파일 포인터를 반환하다.
    fgetc(FILE *fp) //파일포인터로부터 char 하나를 읽어온다
	fputc(int ch, FILE *fp) 파일포인터에 ch를 저장한다. 
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수
[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*src, *dst;
    int		ch;

    if (argc != 3)  {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        exit(1);
    }

    if ((src = fopen(argv[1], "rt")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    if ((dst = fopen(argv[2], "wt")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    while ((ch = fgetc(src)) != EOF)  {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);
}