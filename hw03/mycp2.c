#include <stdio.h>

#define	MAX_BUF	1024
/*===============================================================
[Program Name] : mycp2.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 binary로 read하고 반환받은 포인터를 src에저장
    - argv[2]으로 받은 파일을 fopen해서 binary로 write하고 반환받은 포인터를 dst에 저장
	- fopen시 반환 값이 NULL이면 에러메시지를 출력하고 종료한다 
   - fread()를 통해 src에 있는 바이너리인 오브젝트 size 1짜리를 MAX_BUF만큼의 개수를 buf에 읽어서 읽은 bytes만큼 반환한다(count)
    - fwrite()를 통해 buf에 있는 내용인 size 1짜리 오브젝트를 count만큼 dst에 write한다
    - src에 있는 binary를 dst에 다 옮겼으면 종료한다.
    - fclose를 통해 파일을 닫는다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오
픈하고 파일 포인터를 반환하다.
    fread(void *ptr, size_t size, size_t nobj, FILE *fp) //fp에서 size짜리 오브젝트를 nobj만큼 읽어서 ptr에 저장한다.
    fwrite(void *ptr, size_t size, size_t nobj, FILE *fp) //size짜리 오브젝트를 nobj만큼 ptr에 있는 내용을 fp에 write한다.
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수
[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*src, *dst;
    char	buf[MAX_BUF];
    int		count;

    if (argc != 3)  {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        exit(1);
    }

    if ((src = fopen(argv[1], "rb")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    if ((dst = fopen(argv[2], "wb")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    while ((count=fread(buf,1,MAX_BUF,src))>0)  {
        fwrite(buf, 1, count, dst);
    }

    fclose(src);
    fclose(dst);
}