#include <stdio.h>
/*===============================================================
  [Program Name] : output.c
  [Description] : print the string formatting with type
  [Input] :
  [Output] :  print the string formatting with type //  char, char array(string), int, hexadecimal with state that the alphabet is capitalized, long, up to the fourth decimal with place float,up to the second decimal place with double, pointer. //  putchar is printing the char c,  puts is printing char array s
  [Calls] :
  [특기사항] :
  ==================================================================*/
main()
{
    char c = 'a', s[] = "hello";
    int i = 100; long l = 99999;
    float f = 3.14; double d = 99.999;
    int *p = &i;

    printf("Output: %c %s %d %#X %ld %.4f %.2lf %p\n", c, s, i, i, l, f, d, p);
    putchar(c);
    puts(s);
}
//
// Created by 김수민 on 2022/11/01.
//
