#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define	MAX_PATH	256
/*===============================================================
[Function Name] : void JustDoIt(char *path)
[Description]   : 
	- opendir 함수를 통해 해당 경로(path)의 dir를 오픈한다
	- 만약 NULL을 반환하면 perror로 에러문구를 출력하고 종료한다
	- 디렉토리 경로인 path를 출력하고 readdir를 통해 opendir를 통해 반환받은 DIR 포인터를 파라미터로 받아서 하나씩 읽은 것은 dep에 저장한다.
	- dep의 d_name값이 현재 디렉토리이거나 부모 디렉토리인 . ..일 경우 넘기고 아닐 경우엔 d_name을 출력한다.
	- rewinddir를 통해 dp 포인터를 처음으로 되돌린다. 그 후에 다시 똑같은 작업을 반복하는데 이번에는 디렉토리 안에 디렉토리를 출력하기 위한 작업을 하기 위해 fullpath을 path/d_name처럼 만들고 lstat을 통해 fullpath의 status를 statbuf에 저장한다.
	- statbuf의 st_mode가 dir인 경우에는 다시 JustDoIt 함수를 반복해서 그 안에 있는 파일들과 디렉토리들을 출력하도록 한다.
[Input]         :
[Output]        :
[Call By]       :	        
    Main()
[Calls]         :	        
    opendir() //해당 path의 디렉토리를 오픈하는 함수로서 DIR 포인터를 반환
	strcmp() // 파라미터로 받은 두개의 str을 비교하는 함수로 같으면 0을 반환
	rewinddir() // dir포인터를 처음으로 옮기는 함수
	readdir() // DIR 포인터를 파라미터로 받아서 dirent라는 구조체를 반환
	strcpy() // str을 복사하는 함수
	strcat() // 첫번째 오는 파라미터str 뒤에 두번째로 오는 파라미터의 값을 덧붙이는 함수
	lstat() // 파일의 status를 가져오는 함수로서 l은 링크파일인 경우 링크의 status를 가져오는 함수
	closedir() // 열었던 dir를 닫는 함수
[Given]         :
    char *path //디렉토리 경로인 path를 입력 파라미터로 받는다
[Returns]       :
    Nothing
==================================================================*/
void
JustDoIt(char *path)
{
    DIR				*dp;
    struct dirent	*dep;
    struct stat		statbuf;
    char			fullpath[MAX_PATH];

    if ((dp = opendir(path)) == NULL)  {
        perror("opendir");
        exit(0);
    }

    printf("\n%s:\n", path);
    while (dep = readdir(dp))  {
        if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
            continue;
        printf("%s\n", dep->d_name);
    }

    rewinddir(dp);
    while (dep = readdir(dp))  {
        if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
            continue;
        strcpy(fullpath, path);
        strcat(fullpath, "/");
        strcat(fullpath, dep->d_name);
        if (lstat(fullpath,&statbuf)<0)  {
            perror("lstat");
            exit(1);
        }
        if (S_ISDIR(statbuf.st_mode))  {
            JustDoIt(fullpath);
        }
    }

    closedir(dp);
}
/*===============================================================
[Program Name] : mylsr.c
[Description]  :
	- JustDoIt함수를 파라미터로 현재 디렉토리를 의미하는 . 을 넘긴다
	- 이 파일은 현재 디렉토리의 파일과 디렉토리를 출력하는 파일로 디렉토리 안에 있는 디렉토리 내용들도 출력한다. ls -R 커맨드와 동일한 작업을 수행한다.
[Input]        : 
[Output]       :
[Calls]        :            
	JustDoIt() // ls -R 작업을 수행하기 위해 작성한 함수
[특기사항]     : 
===============================================================*/
main()
{
    JustDoIt(".");
}