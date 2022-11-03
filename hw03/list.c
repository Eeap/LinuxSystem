#include <stdio.h>

#define	MAX_BUF	256
/*===============================================================
[Program Name] : list.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 text로 read하고 파일 포인터를 반환받는다
	- fopen시 반환 값이 NULL이면 에러메시지를 출력하고 종료한다 
	- fgets를 통해서 fd에서 MAX_BUF만큼 buf에 한 라인씩 받아서 저장한다.
	- printf 를 통해 줄 번호와 해당 줄의 내용을 출력한다
	- fclose를 통해 파일을 닫는다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오픈하고 파일 포인터를 반환하다.
	fgets(char *buf, int max, FILE *fp) // 파일포인터로부터 max만큼 한 라인씩 읽어서 buf에 저장한다
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수
[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*fp;
    char	buf[MAX_BUF];
    int		line;

    if (argc != 2)  {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    if ((fp = fopen(argv[1], "rt")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    line = 1;
    while (fgets(buf,MAX_BUF,fp))  {
        printf("%4d: %s", line++, buf);
    }

    fclose(fp);
}