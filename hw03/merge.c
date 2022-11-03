#include <stdio.h>

#define	MAX_BUF	1024
/*===============================================================
[Program Name] : merge.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 binary로 read하고 반환받은 포인터를 src1 에저장
    - argv[2]으로 받은 파일을 fopen해서 binary로 read하고 반환받은 포인터를 src2에 저장
    - argv[3]으로 받은 파일을 fopen해서 binary로 write하고 반환받은 포인터를 dst에 저장
    - fopen 시 NULL을 반환하면 에러메시지를 출력하고 종료한다.
    - fread를 통해 src1에 있는 내용을 사이즈가 1인 오브젝트로 MAX_BUF만큼 읽고 buf에 저장한다
	- fwrite를 통해 buf에 있는 사이즈가 1인 오브젝트를 src1에서 읽은 만큼인 count만큼 읽어서 dst에 write한다
	- src2도 위의 과정처럼 읽고 buf에 저장하고 읽은 만큼인 count만큼 dst에 write한다.
	- src1에 있는 내용과 src2에 있는 내용을 전부 다 dst에 write(merge과정) 하면 종료한다
    - fclose를 통해 파일을 닫는다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오
픈하고 파일 포인터를 반환하다.
    fread(void *ptr, size_t size, size_t nobj, FILE *fp) //fp에서 size짜리 오브젝
트를 nobj만큼 읽어서 ptr에 저장한다.
    fwrite(void *ptr, size_t size, size_t nobj, FILE *fp) //size짜리 오브젝트를 nobj만큼 ptr에 있는 내용을 fp에 write한다.
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수

[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*src1, *src2, *dst;
    char	buf[MAX_BUF];
    int		count;

    if (argc != 4)  {
        fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
        exit(1);
    }

    if ((src1 = fopen(argv[1], "rb")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    if ((src2 = fopen(argv[2], "rb")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    if ((dst = fopen(argv[3], "wb")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    while ((count=fread(buf,1,MAX_BUF,src1))>0)  {
        fwrite(buf, 1, count, dst);
    }

    while ((count=fread(buf,1,MAX_BUF,src2))>0)  {
        fwrite(buf, 1, count, dst);
    }

    fclose(src1);
    fclose(src2);
    fclose(dst);
}