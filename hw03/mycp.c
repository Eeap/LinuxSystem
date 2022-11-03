#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define	MAX_BUF	1024
/*===============================================================
[Program Name] : mycp.c
[Description]  :
	- argv[1]으로 받은 파일을 read로 오픈해서 fd1에 저장
	- argv[2]로 받은 파일을 write와 creat, trunc모드로 오픈해서 fd2에 저장하고 각각(U,G,O)의 권한인 rwx를 644(앞에 0은 8진수를 의미)로 설정
	- open시 반환 값이 0 보다 작으면 에러메시지를 출력하고 종료한다.
	- read를 통해 fd1에 있는 내용을 MAX_BUF만큼 읽어서 buf에 저장하고 반환받은 count만큼 fd2에 buf를 write한다.
	- fd1에서 fd2로의 복사가 끝나면 close한다
[Input]        : 
	char *argv[] //실행 시 입력받은 파일들
[Output]       :
    
[Calls]        :            
    write(int fd, void *buf, size_t nbytes) // nbytes만큼 buf에 있는 내용을 fd에 저장
    read(int fd, void *buf, size_t nbytes) // nbytes만큼 fd에 읽는 내용을 buf에 읽어서 저장
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
    exit() //프로그램을 종료
    close(int fd) //파일을 닫는 함수
[특기사항]     : 
===============================================================*/
main(int argc, char *argv[])
{
    int 	fd1, fd2, count;
    char	buf[MAX_BUF];

    if (argc != 3)  {
        printf("Usage: %s source destination\n", argv[0]);
        exit(1);
    }

    if ((fd1 = open(argv[1], O_RDONLY)) < 0)  {
        perror("open");
        exit(1);
    }

    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)  {
        perror("open");
        exit(1);
    }

    while ((count = read(fd1,buf,MAX_BUF)) > 0)  {
        write(fd2, buf, count);
    }

    close(fd1);
    close(fd2);
}