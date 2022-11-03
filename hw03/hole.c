#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
/*===============================================================
[Program Name] : hole.c
[Description]  :
    - file.hole이라는 파일을 만들어서 0부터 1023까지 포인터를 이동해서 거기에서 널값을 write하고 닫는데 그러면 그 앞에는 모두 0으로 채워짐.
	- lseek와 creat한 값이 0보다 작으면 에러메시지를 출력하고 종료한다.
[Input]        :
[Output]       :

[Calls]        :
    creat(char *pathname, mode_t mode) //파일을 생성
	lseek(int fd, off_t offset, int whence) //whence에서 offset만큼 파일 포인터를 이동
	perror() //어떤 에러메시지가 발생했는지 화면에 출력
	exit() //프로그램을 종료
	close(int fd) //파일을 닫는 함수
[특기사항]     : file.hole이라는 파일에 결과가 저장
===============================================================*/
main()
{
    int 	fd;
    char	ch = '\0';

    if ((fd = creat("file.hole", 0400)) < 0)  {
        perror("creat");
        exit(1);
    }

    if (lseek(fd, 1023, SEEK_SET) < 0)  {
        perror("lseek");
        exit(1);
    }
    write(fd, &ch, 1);

    close(fd);
}
