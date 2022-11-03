#include <stdio.h>
#include <stdlib.h>
/*===============================================================
[Function Name] : myexit1()
[Description]   : printf로 안에 있는 내용을 출력하는 함수
[Input]         :
[Output]        :
[Call By]       :	        
    Main()
[Calls]         :	        
[Given]         :
[Returns]       :
==================================================================*/
void
myexit1()
{
    printf("first exit handler\n");
}
/*===============================================================
[Function Name] : myexit2()
[Description]   : printf로 안에 있는 내용을 출력하는 함수
[Input]         :
[Output]        :
[Call By]       :	        
    Main()
[Calls]         :	        
[Given]         :
[Returns]       :
==================================================================*/
void
myexit2()
{
    printf("second exit handler\n");
}
/*===============================================================
[Program Name] : exit.c
[Description]  : 
	- atexit함수를 통해 exit handler를 등록한다
	- 그러면 나중에 exit func이 호출이 되면 내가 등록한 exit handler가 수행된뒤 exit된다.
[Input]        :
[Output]       :
[Calls]        :            
    atexit() //exit handler함수를 등록하는 함수 
    perror() // 에러메시지 출력
[특기사항]     : 
==================================================================*/
main()
{
    /* Add myexit2 to exit functions */
    if (atexit(myexit2))  {
        perror("atexit");
        exit(1);
    }

    if (atexit(myexit1) != 0)  {
        perror("atexit");
        exit(1);
    }

    if (atexit(myexit1) != 0)  {
        perror("atexit");
        exit(1);
    }

    printf("main is done\n");
}