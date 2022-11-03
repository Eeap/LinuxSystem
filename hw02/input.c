#include <stdio.h>
/*===============================================================
  [Program Name] : input.c
  [Description] : Receive input with scanf and output with printf. getchar is receiving input with char and putchar is printing char c. gets is receiving input with char array s and puts is printing char array s
  [Input] : in order of type // char, char array(string), int, long, float, double
  [Output] : format and print by type // char, char array, int, long, up to the fourth decimal place with float,  up to the second decimal place with double
  [Calls] :
  [특기사항] :
  ==================================================================*/
main()
{
    char c, s[80];
    int i; long l;
    float f; double d;
    scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d);
    printf("Output: %c %s %d %ld %.4f %.2lf\n", c, s, i, l, f, d);

    c = getchar();
    putchar(c);

    gets(s);
    puts(s);
}
//
// Created by 김수민 on 2022/11/01.
//
