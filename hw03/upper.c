#include <stdio.h>

#define MAX_BUF 256
/*===============================================================
[Program Name] : upper.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 text를 read모드로 여는데  반환받은 포인터를 src 에저장
	- argv[2]으로 받은 파일을 fopen해서 text를 write모드로 여는데 반환받은 포인터를 dst 에저장
    - fopen 시 NULL을 반환하면 에러메시지를 출력하고 종료한다.
    - fgets을 통해 src에서 한줄을 MAX_BUF만큼 입력받아 buf에 저장한다
	- 인덱스를 통해 buf에 널값이 저장되어 있는 인덱스까지 반복문을 도는데 만약 buf[i] char 값이 97이상이고 122이하면 (소문자에 해당) 32를 빼줘서 대문자로 만든다.
	- fputs을 통해 buf에 있는 내용을 dst에 저장한다.
	- 소문자를 대문자로 다 바꿨으면 fclose를 통해 파일을 닫고 종료한다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오픈하고 파일 포인터를 반환하다.
    fgets(char *buf, int max, FILE *fp) // fp로부터 max만큼 라인 하나를 읽어서 buf에 저장
	fputs(char *buf, FILE *fp) // buf에 저장된 라인 하나를 fp에 저장
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수

[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE    *src, *dst;
    char    buf[MAX_BUF];

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

    while (fgets(buf,MAX_BUF,src))  {
        for (int i =0; buf[i]!='\0'; i++){
            if (buf[i]>=97 && buf[i] <=122){
                buf[i]-=32;
            }
        }
        fputs(buf, dst);
    }

    fclose(src);
    fclose(dst);
}