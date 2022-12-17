#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
/*===============================================================
[Function Name] : myusleep(int secs, int usecs)
[Description]   :
    - 이 함수는 select라는 함수를 이용해서 단순히 입력받은 시간만큼 기다리는 함수이다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    select() // fd_set에 있는 fd를 tm에 저장된 시간만큼 기다리는 함수
[Given]         :
[Returns]       :
=================================================================*/
void
myusleep(int secs, int usecs)
{
    struct timeval  tm;

    tm.tv_sec = secs;
    tm.tv_usec = usecs;

    if (select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &tm) < 0)  {
        perror("select");
        return;
    }
}
/*===============================================================
[Program Name] : myusleep.c
[Description]  :
    - 이 프로그램은 1.5초 동안 sleep하는 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
[특기사항]     :
==================================================================*/
main()
{
    printf("Sleep for 1.5 seconds.....\n");
    myusleep(1, 500000);
}
