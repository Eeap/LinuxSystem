#include <stdio.h>

#define	MAX_BUF	256
/*===============================================================
[Program Name] : tcp2.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 text로 read하고 반환받은 포인터를 src에 >저장
    - argv[2]으로 받은 파일을 fopen해서 text로 write하고 반환받은 포인터를 dst에저장
	- fopen시 반환 값이 NULL이면 에러메시지를 출력하고 종료한다 
    - fgets()를 통해 src에 있는 텍스트를 MAX_BUF만큼 buf에 한 라인씩 읽는다
	- fputs()를 통해 buf에 있는 내용을 dst에 저장한다.
	- src에 있는 text를 dst에 다 옮겼으면 종료한다.
    - fclose를 통해 파일을 닫는다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오
픈하고 파일 포인터를 반환하다.
    fgets(char *buf, int max , FILE *fp) //파일포인터로부터 max만큼 한 라인을 읽고 buf에 저장한다.
    fputs(char *str, FILE *fp) 파일포인터에 str를 저장한다. 
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수
[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*src, *dst;
    char	buf[MAX_BUF];

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

    while (fgets(buf,MAX_BUF,src)!=NULL)  {
        fputs(buf, dst);
    }

    fclose(src);
    fclose(dst);
}