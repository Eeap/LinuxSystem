#include <stdio.h>

enum { FALSE, TRUE };

/*===============================================================
[Function Name] : void conv(char *fname)
[Description]   : 
    - fname파일을 text로 read해서 오픈한 파일 포인터를 src에 저장한다
	- fopen시 NULL일 경우 에러 메시지를 출력하고 종료한다
	- strcpy를 통해 fdest에 fname 파일 이름값을 복사하고 strcat을 통해.t를 붙인다.
	- fopen으로 fdest라는 파일 이름을 text로 write모드로 오픈하고 dst에 그 포인터를 저장한다.
	- 여기서도 fopen시 NULL일 경우 에러 미시지를 출력하고 종료한다.
	- src에서 fgetc를 통해 char 하나씩 읽은 것을 ch에 저장하고 first가 true고 ch가 탭키이면 dst에 탭을 추가한다(4칸).
	- 아닐 경우에는 ch를 dst에 저장하고 first가 트루인 경우 false로 바꿔주고 ch가 엔터인 다음 줄로 넘어갈때 다시 first를 true로 해서 tab을 추가할 수 있게 해준다.
	- 파일에 끝에 도달해 다 읽었을 경우 fclose를 통해 파일을 닫는다.	 
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
    fopen(char *pathname, char *type) // 입력 받은 파일을 타입에 맞춰서 파일을 오픈하고 파일 포인터를 반환하다.
	strcpy(dst,src) // dst에 src값을 복사
	strcat(dst, src) //dst 뒤에 src값을 붙인다
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
	fgetc(FILE *fp) // char하나 읽어서 반환
	fputc(int ch, FILE *fp) fp에 ch 저장
	fclose(FILE *fp) //파일을 닫는 함수
[Given]         :
    char *fname; // 파일 이름
[Returns]       :
    Nothing
==================================================================*/
void
conv(char *fname)
{
    FILE	*src, *dst;
    char	fdest[40];
    int		ch, first;

    if ((src = fopen(fname, "rt")) == NULL)  {
        perror("fopen");
        return;
    }

    strcpy(fdest, fname);
    strcat(fdest, ".t");
    if ((dst = fopen(fdest, "wt")) == NULL)  {
        perror("fopen");
        return;
    }

    first = TRUE;
    while ((ch = fgetc(src)) != EOF)  {
        if (first && ch == '\t')  {
            fputc(' ', dst);
            fputc(' ', dst);
            fputc(' ', dst);
            fputc(' ', dst);
        }
        else  {
            fputc(ch, dst);
            if (first)
                first = FALSE;
            if (ch == '\n')
                first = TRUE;
        }
    }

    fclose(src);
    fclose(dst);
}
/*===============================================================
[Program Name] : access.c
[Description]  :
	- 입력받은 argv 수만큼 while문을 반복해서 conv함수를 실행한다.(conv은 라인 앞에 tab을 만드는 함수이다)
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
	- conv(char *fname) // fname를 입력 받아 라인 앞에 탭키를 달아서 새로운 텍스트 파일을 만드는 함수
[특기사항]     : $(fname).t라는 파일에 tab한 텍스트를 저장
===============================================================*/
main(int argc, char *argv[])
{
    while (--argc)  {
        conv(argv[argc]);
    }
}