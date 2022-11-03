#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
/*===============================================================
[Program Name] : stat.c
[Description]  :
    - 이 파일은 bar와 foo라는 파일을 권한을 다르게 해서 만드는 파일이다
	- umask를 이용해서 해당 비트를 끌건지 결정하고 bar 파일의 경우에는 해당 비트를 끄지 않고 creat시 user는 rw권한을 주고 group은 rw권한을 주고 other는 rw권한을 준다.
	- foo파일의 경우엔 권한을 bar와 똑같이 주고 creat 하지만 umask를 이용해 group의 경우 rw를 그고 other의 경우엔 rw권한을 끄고 만든다.
[Input]        :
    char *argv[] //실행 시 입력받은 파일들
[Output]       :
[Calls]        :
	umask(mode_t cmask) // cmask에 오는 특정 모드를 끈다
	creat(char *pathname, mode_t mode) //해당 mode로 파일을 하나 만든다
    perror() //어떤 에러메시지가 발생했는지 화면에 출력
[특기사항]     :
===============================================================*/
main()
{
    umask(0);
    if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                     S_IROTH | S_IWOTH) < 0)  {
        perror("creat");
        exit(1);
    }

    /* Set file mode creation mask: S_IRGRP, S_IWGRP, S_IROTH, S_IWOTH */
    /* umask */
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                     S_IROTH | S_IWOTH) < 0)  {
        perror("creat");
        exit(1);
    }
}
//
// Created by 김수민 on 2022/11/01.
//
