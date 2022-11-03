#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
/*===============================================================
[Function Name] : void printDir(char *argv)
[Description]   :
    - opendir 함수를 통해 해당 경로(path)의 dir를 오픈한다
    - 만약 NULL을 반환하면 perror로 에러문구를 출력하고 종료한다
    - 디렉토리 경로인 path를 출력하고 readdir를 통해 opendir를 통해 반환받은 DIR 포인터를 파라미터로 받아서 하나씩 읽은 것은 dep에 저장한다.
    - dep의 d_name값이 현재 디렉토리이거나 부모 디렉토리인 . ..일 경우 넘기고 아닐 경우엔 ls -l을 수행하기 위한 작업을 한다.
	- 먼저 파일의 타입과 권한을 lstat을 통해 알아낸 뒤에 출력한다.
	- 그 다음 몇개의 링크가 연결되어 있는지 출력하고 그 다음 파일의 소유자와 group name을 출력한다.
	- 그 다음 순서대로 파일의 사이즈 변경 시간 마지막으로 파일의 이름을 출력하는데 만약 파일의 mode가 l인 심볼릭 링크의 경우 어디에 연결되었는지 출력하기 위해 readlink 함수를 이용해서 buff에 읽어온다.
	- 출력을 마친 후에는 closedir로 디렉토리를 닫는다
[Input]         :
[Output]        :
[Call By]       :
    Main()
[Calls]         :
    opendir() //해당 path의 디렉토리를 오픈하는 함수로서 DIR 포인터를 반환
    strcmp() // 파라미터로 받은 두개의 str을 비교하는 함수로 같으면 0을 반환
    rewinddir() // dir포인터를 처음으로 옮기는 함수
    readdir() // DIR 포인터를 파라미터로 받아서 dirent라는 구조체를 반환
    lstat() // 파일의 status를 가져오는 함수로서 l은 링크파일인 경우 링크의 status를 가져오는 함수
    getpwuid() //파라미터로 받은 uid를 통해 user 상세 정보를 반환하는 함수
	getgrgid() // 파라미터로 받은 gid를 통해 group 상세 정보를 반환하는 함수
	localtime() //파라미터로 받은 시간을 사람들이 알아볼 수 있는 시간 정보를 반환하는 함수
	strftime() // 날짜, 시간 정보 등을 스트링으로 첫번째로 파라미터로 넘어오는 변수에 저장하는 함수
	readlink() // 심볼릭 링크의 정보를 읽어오는 함수
	closedir() // 열었던 dir를 닫는 함수
[Given]         :
    char *argv //출력할 경로를 입력 파라미터로 받는다
[Returns]       :
    Nothing
==================================================================*/

void printDir(char *argv)
{
    DIR *dp;
    struct dirent *dep;
    struct passwd *pwd;
    struct group *g;
    struct stat statbuf;
    char f[128];
    char *mode;
    long sum=0;
    if ((dp = opendir(argv)) == NULL)  {
        perror("opendir");
        exit(0);
    }
    while(dep=readdir(dp)){
        if (lstat(dep->d_name,&statbuf) < 0)  {
            perror("lstat");
            continue;
        }
        if (strcmp(dep->d_name,".") == 0 || strcmp(dep->d_name,"..") == 0)
            continue;
        sum+=statbuf.st_blksize;
    }
    printf("total %ld\n",sum/1000);
    rewinddir(dp);
    while (dep=readdir(dp)) {
        if (lstat(dep->d_name,&statbuf) < 0)  {
            perror("lstat");
            continue;
        }
        if (strcmp(dep->d_name,".") == 0 || strcmp(dep->d_name,"..") == 0)
            continue;
        if (S_ISREG(statbuf.st_mode))
            mode = "-";
        else if (S_ISDIR(statbuf.st_mode))
            mode = "d";
        else if (S_ISCHR(statbuf.st_mode))
            mode = "c";
        else if (S_ISBLK(statbuf.st_mode))
            mode = "b";
        else if (S_ISLNK(statbuf.st_mode))
            mode = "l";
        printf("%s", mode);
        printf((statbuf.st_mode & S_IRUSR) ? "r":"-");
        printf((statbuf.st_mode & S_IWUSR) ? "w":"-");
        printf((statbuf.st_mode & S_ISUID) ? "S":((statbuf.st_mode & S_IXUSR) ? "x":"-"));
        printf((statbuf.st_mode & S_IRGRP) ? "r":"-");
        printf((statbuf.st_mode & S_IWGRP) ? "w":"-");
        printf((statbuf.st_mode & S_IXGRP) ? "x":"-");
        printf((statbuf.st_mode & S_IROTH) ? "r":"-");
        printf((statbuf.st_mode & S_IWOTH) ? "w":"-");
        printf((statbuf.st_mode & S_IXOTH) ? "x":"-");
        printf(" %ld ",statbuf.st_nlink);
        pwd = getpwuid(1011);
        g = getgrgid(1050);
        printf("%s %s ",pwd->pw_name, g->gr_name);
        printf("%5ld ",(long)statbuf.st_size);
        struct tm *ct = localtime(&statbuf.st_mtime);
        strftime(f,128,"%b %d %H:%M ",ct);
        printf("%s ",f);
        if (strcmp(mode,"l")==0){
            char buff[1024];
            int n;
            if ((n=readlink(dep->d_name,buff,1024)) == -1){
                perror("readlink");
                exit(1);
            }
            buff[n]='\0';
            printf("%s -> %s\n", dep->d_name,buff);
        }
        else{
            printf("%s\n", dep->d_name);
        }
    }
    closedir(dp);
}
/*===============================================================
[Program Name] : mylsr.c
[Description]  :
    - printDir함수를 파라미터로 argv로 따로 넘어온게 없으면 현재 디렉토리인 .을 넘기고 있을 경우엔 해당 argv[1]을 넘긴다
    - 이 파일은 디렉토리의 파일과 디렉토리의 정보를 출력하는 파일이다. ls -l 커맨드와 동일한 작업을 수행한다.
[Input]        :
[Output]       :
[Calls]        :
    printDir() // ls -l 작업을 수행하기 위해 작성한 함수
[특기사항]     :
===============================================================*/


int main(int argc, char *argv[])
{
    if (argc==1){
        printDir(".");
    } else if (argc==2){
        printDir(argv[1]);
    }

    return 0;
}