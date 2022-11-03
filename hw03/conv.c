#include <stdio.h>
#include <string.h>
#include "record.h"
/*===============================================================
[Program Name] : conv.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 text로 read하고 반환받은 포인터를 src 에저장
    - argv[2]으로 받은 파일을 fopen해서 binary로 write하고 반환받은 포인터를 dst에 저장
    - fopen 시 NULL을 반환하면 에러메시지를 출력하고 종료한다.
    - fgets을 통해 record 단위로 read를 하고 src에서 SMAX만큼 한줄 읽어서 rec.stud에 저장한다.
	- strchr를 통해 '\n'의 포인터를 찾아서 널값으로 바꾼다
	- 아래도 마찬가지로 src에서 read하고 레코드 객체에 저장하고 '\n'가 있는 곳을 널값으로 바꾼다.
	- stud와 num, dept에 각각의 값을 다 저장한 후 fwrite를 통해 dst에 record 객체 하나를 그 사이즈만큼 write한다.(바이너리로 write하도록 파일을 open했다)
	- 파일을 다 읽어서 text를 binary로 convert를 다했으면 종료한다.
	- fclose를 통해 파일을 닫는다
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오
픈하고 파일 포인터를 반환하다.
    fgets(char *buf, int max, FILE *fp) // fp로부터 max만큼 한줄을 읽어서 buf에 저장한다.
	*strchr(const char *str, int c) // str에서 c의 위치를 찾아서 포인터를 반환해준다
	fwrite(void *ptr, size_t size, size_t nobj, FILE *fp) //size짜리 오브젝트를 obj만큼 ptr에 있는 내용을 fp에 write한다.
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수

[특기사항]     : test.in 파일에 작성된 텍스트 내용을 읽어서 test.out으로 convert한 내용을 출력
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*src, *dst;
    Record	rec;

    if (argc != 3)  {
        fprintf(stderr, "Usage: %s source dest\n", argv[0]);
        exit(1);
    }

    if ((src = fopen(argv[1], "rt")) == NULL)  {
        perror("fopen");
        exit(1);
    }
    if ((dst = fopen(argv[2], "wb")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    while (fgets(rec.stud, SMAX, src))  {
        *strchr(rec.stud, '\n') = '\0';
        fgets(rec.num, NMAX, src);
        *strchr(rec.num, '\n') = '\0';
        fgets(rec.dept, DMAX, src);
        *strchr(rec.dept, '\n') = '\0';

        fwrite(&rec,sizeof(rec),1,dst);

    }

    fclose(src);
    fclose(dst);
}