#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include "record.h"
/*===============================================================
[Function Name] : void print_record(Record *rp)
[Description]   : 
	- record에 있는 stud와 num, dept를 출력한다.
[Input]         :
[Output]        :
[Call By]       :	        
    Main()
[Calls]         :	        
    puts() //string을 출력하는 함수
[Given]         :
	Recor *rp; //record 객체 포인터
[Returns]       :
    Nothing
==================================================================*/

void
print_record(Record *rp)
{
    puts(rp->stud);
    puts(rp->num);
    puts(rp->dept);
}
/*===============================================================
[Program Name] : access.c
[Description]  :
    - argv[1]으로 받은 파일을 fopen해서 binary를 read모드로 여는데 write도 해서 반환받은 포인터를 fp 에저장
    - fopen 시 NULL을 반환하면 에러메시지를 출력하고 종료한다.
    - fread를 통해 fp에 있는 내용을 rec사이즈만큼 한개 읽어서 rec객체에 저장한 후 print_record 메소드를 통해 rec객체를 출력한다
    - rewind를 통해 fp를 맨 처음으로 위치시킨다
	- 섞어서 출력하기 위해서 fseek를 통해 파일 포인터 위치를 sizeof(rec)*2L만큼 이동한다. 그 다음 fread를 통해 rec객체 하나를 fp로부터 읽고 print_record를 통해 record 객체를 출력한다
	- 아래도 마찬가지로 사이즈*5L만큼 이동해서 읽고 출력하고 그 다음도 사이즈*1L만큼 이동해서 읽고 출력하고 , 사이즈*3L만큼 이동해서 읽고 출력하고, 사이즈*0L만큼 이동해서 읽고 출력하고, 사이즈*4L만큼 이동해서 읽고 출력한다.
	- 다음은 업데이트 과정인데 size*2L만큼 이동한다음 fp로 rec 객체를 1개 읽고 rec.dept의 값을 Movie로 strcpy를 통해 바꾼 후 다시 그 위치로 이동해서 size*2L에서 부터 record의 사이즈만큼 rec객체 한개를 fp에 write한다. 
	- 이번에는 사이즈*5L에 있는 레코드 객체의 dept값을 Baseball로 strcpy를 통해 바꾼 후 마찬가지로 다시 그 위치로 fseek를 통해 이동한 후 fwrite를 통해 fp에 레코드 객체르 write한다.
	- rewind를 통해 파일포인터를 처음으로 위치시키고 fread를 통해 처음부터 끝까지 다시 print_record로 rec객체들을 출력한다.
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
	fseek(FILE *fp, long offset, int whence) //파일 포인터를 whence 기준으로 offset만큼 이동
	rewind(FILE *fp) // fp를 처음으로 이동
	getchar() // char 한개를 입력 받음. 여기서는 아무키나 치면 다음 리스트가 출력
	print_record(Record *rp) //record 객체를 출력
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    fclose(FILE *fp) //파일을 닫는 함수

[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    FILE	*fp;
    Record	rec;

    if (argc != 2)  {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }

    if ((fp = fopen(argv[1], "r+b")) == NULL)  {
        perror("fopen");
        exit(1);
    }

    printf("-----Ordered Record List-----\n");

    while (fread(&rec,sizeof(rec),1,fp))  {
        print_record(&rec);
    }
    rewind(fp);
    getchar();

    printf("-----Shuffled Record List (3, 6, 2, 4, 1, 5)-----\n");

    fseek(fp, sizeof(rec)*2L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    print_record(&rec);

    fseek(fp, sizeof(rec)*5L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    print_record(&rec);

    fseek(fp, sizeof(rec)*1L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    print_record(&rec);

    fseek(fp,sizeof(rec)*3L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    print_record(&rec);

    fseek(fp, sizeof(rec)*0L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    print_record(&rec);

    fseek(fp, sizeof(rec)*4L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    print_record(&rec);
    getchar();

    printf("-----Updated Record List-----\n");

    fseek(fp, sizeof(rec)*2L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    strcpy(rec.dept, "Movie");
    fseek(fp,sizeof(rec)*2L, SEEK_SET);
    fwrite(&rec, sizeof(rec), 1, fp);

    fseek(fp, sizeof(rec)*5L, SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);
    strcpy(rec.dept, "Baseball");
    fseek(fp, sizeof(rec)*5L, SEEK_SET);
    fwrite(&rec, sizeof(rec), 1, fp);

    rewind(fp);
    while (fread(&rec, sizeof(rec), 1, fp))  {
        print_record(&rec);
    }

    fclose(fp);
}