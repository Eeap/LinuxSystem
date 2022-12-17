#include <stdio.h>
/*===============================================================
[Program Name] : order.c
[Description]  :
    - 이 프로그램은 big-endian과 little-endian을 확인하기 위한 프로그램이다.
[Input]        :
[Output]       :
[Calls]        :
[특기사항]     :
==================================================================*/
main()
{
    int     a = 0x12345678;
    char    *p = (char *)&a;

#if 1
    printf("Address %p: %#x\n", p, *p); p++;
    printf("Address %p: %#x\n", p, *p); p++;
    printf("Address %p: %#x\n", p, *p); p++;
    printf("Address %p: %#x\n", p, *p); p++;
#else
    printf("Address %p: %#x\n", p, *p++);
    printf("Address %p: %#x\n", p, *p++);
    printf("Address %p: %#x\n", p, *p++);
    printf("Address %p: %#x\n", p, *p++);
#endif
}
