#include <stdio.h>
#include <unistd.h>

#define	MAX_BUF	1024
/*===============================================================
[Function Name] : long filesize(FILE *fp)
[Description]   : 
    - ftell을 통해 현재 파일 포인터를 저장하고 fseek로 파일 포인터를 끝으로 위치 시킨 후 다시 ftell을 통해 파일의 끝의 길이를 size에 저장한 후 fseek로 원래 자리로 돌려놓은 다음 size를 반환한다
[Input]         :
    FILE *fp;     // 파일 포인터 객체
[Output]        :
[Call By]       :	        
    Main()
[Calls]         :	        
    Nothiong
[Given]         :
    Nothing
[Returns]       :
    long size; // 파일의 크기 리턴
===============================================================*/
long
filesize(FILE *fp)
{
    long	cur, size;

    cur = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, cur, SEEK_SET);
    return(size);
}
/*===============================================================
[Program Name] : split.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 binary로 read하고 반환받은 포인터를 src에
저장
    - argv[2]으로 받은 파일을 fopen해서 binary로 write하고 반환받은 포인터를 dst1에 저장
	- argv[3]으로 받은 파일을 fopen해서 binary로 write하고 반환받은 포인터를 dst2에 저장
	- fopen 시 NULL을 반환하면 에러메시지를 출력하고 종료한다.
	- filesize 함수를 통해 src 파일의 사이즈를 리턴 받고 반으로 나눈 값을 size에 저장한다.
	- count에 size가 MAX_BUF보다 클 경우 MAX_BUF를 저장해서 fread를 통해 src에서 count만큼의 size가 1인 오브젝트를 읽고 buf에 저장한다.
	- 그 다음 fwrite를 통해 dst1에 buf에 있는 내용을 size가 1인 오브젝트를 count만큼 write한다.
	- size값에 읽고 쓴 count만큼 빼서 size가 0보다 작을때까지 반복한다.
	- dst1에 반절을 나누고 나머지 반절은 dst2에 저장하는 작업을 한다.
	- 위의 과정처럼 fread를 통해 MAX_BUF만큼 사이즈가 1인 오브젝트를 buf에 쓰고 fwrite를 통해 dst2에 저장한다. 이 반복문을 더이상 읽을게 없을때까지 반복한다.
    - src에 있는 내용을 dst1과 dst2에 split했으면 종료한다
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
	filesize(FILE *fp) // 파일 사이즈를 리턴한다.
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수

[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*src, *dst1, *dst2;
    char	buf[MAX_BUF];
    int		count, size;

    if (argc != 4)  {
        fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]);
        exit(1);
    }

    if ((src = fopen(argv[1], "rb")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    if ((dst1 = fopen(argv[2], "wb")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    if ((dst2 = fopen(argv[3], "wb")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    size = filesize(src) / 2;

    while (size > 0)  {
        count = (size > MAX_BUF) ?  MAX_BUF : size;
        fread(buf, 1, count, src);
        fwrite(buf,1,count,dst1);
        size -= count;
    }

    while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
        fwrite(buf,1,count,dst2);
    }

    fclose(src);
    fclose(dst1);
    fclose(dst2);
}