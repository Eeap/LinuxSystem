#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
/*===============================================================
[Program Name] : stat.c
[Description]  :
	- 이 파일은 stat 구조체의 내용을 출력하는 함수이다.
	- 먼저 파일 type이 디렉토리인지 그냥 파일인지 st_mode를 통해 확인하고 그 해당 내용의 값을 mode에 저장한다
	- 그 다음 stat 구조체에 있는 내용인 st_mode, st_ino, st_dev등의 값을 출력한다.
[Input]        : 
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
	- 파일의 type인 mode, stat 구조체 안에 있는 값들
[Calls]        :            
	lstat(char *pathname, struct stat *buf) // lstat은 stat처럼 파일의 status를 얻어오는 함수이지만 링크일때는 링크의 status를 buf에 얻어온다
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    struct stat	statbuf;
    char		*mode;
    int			i;

    for (i = 1 ; i < argc ; i++)  {
        printf("%s: ", argv[i]);
        if (lstat(argv[i],&statbuf) < 0)  {
            perror("lstat");
            continue;
        }
        if (S_ISREG(statbuf.st_mode))
            mode = "regular";
        else if (S_ISDIR(statbuf.st_mode))
            mode = "directory";
        else if (S_ISCHR(statbuf.st_mode))
            mode = "character special";
        else if (S_ISBLK(statbuf.st_mode))
            mode = "block special";
        else if (S_ISFIFO(statbuf.st_mode))
            mode = "FIFO";
        else if (S_ISLNK(statbuf.st_mode))
            mode = "symbolic link";
        else if (S_ISSOCK(statbuf.st_mode))
            mode = "socket";
        printf("%s\n", mode);
        printf("\tst_mode = %d\n", statbuf.st_mode);
        printf("\tst_ino = %d\n", statbuf.st_ino);
        printf("\tst_dev = %d\n", statbuf.st_dev);
        printf("\tst_rdev = %d\n", statbuf.st_rdev);
        printf("\tst_nlink = %d\n", statbuf.st_nlink);
        printf("\tst_uid = %d\n", statbuf.st_uid);
        printf("\tst_gid = %d\n", statbuf.st_gid);
        printf("\tst_size = %d\n", statbuf.st_size);
        printf("\tst_atime = %d\n", statbuf.st_atime);
        printf("\tst_mtime = %d\n", statbuf.st_mtime);
        printf("\tst_ctime = %d\n", statbuf.st_ctime);
        printf("\tst_blksize = %d\n", statbuf.st_blksize);
        printf("\tst_blocks = %d\n", statbuf.st_blocks);
    }
}