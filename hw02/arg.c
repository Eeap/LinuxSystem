#include <stdio.h>
/*===============================================================
[Program Name] : args.c
[Description] : It is a program that outputs argv received as an input one by one. For example, if you give the command with ./args args.c, you output ./args and args.c
[Input] : take argv values
[Output] : print argv values
[Calls] :
[특기사항] :
==================================================================*/
main(int argc, char *argv[])
{
    int i;
    for (i = 0 ; i < argc ; i++)
        printf("argv[%d]=%s\n", i, argv[i]);
}
