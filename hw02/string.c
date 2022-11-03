#include <stdio.h>

/*===============================================================
[Function Name] : int strlen_p(char *str)
[Description]   :
	- Take the character array as a pointer parameter and increase the str pointer one by one to increase the len until the pointer points null value
	- return the string length
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char *str // char pointer
[Returns]       :
	int len // int variables to return the length of a string
==================================================================*/
int
strlen_p(char *str)
{
    int	len = 0;
    while (*str++)  {
        len++;
    }
    return len;
}
/*===============================================================
[Function Name] : int strlen_a(char str[])
[Description]   :
	- It is a function that takes the character array as a pointer parameter(same expression with *str and str[]) and returns the length of the string by approaching the str[] using the indexing method
	- Run a repeat statement by initializing i to zero at first and increasing i one by one to the str[i] containing the null value \0
    - return the string length
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
	char str[] // char pointer, but express with array method
[Returns]       :
    int i //  int variables to return the length of a string
==================================================================*/
int
strlen_a(char str[])
{
    int i;

    for (i = 0 ; str[i] != '\0' ; i++)
        ;
    return i;
}
/*===============================================================
[Function Name] : void strcpy_p(char *dst, char *src)
[Description]   :
    - It is a function that receives the string dst and src as pointer parameters and copies the string from src to dst
	- Run the repetitive statement until the src pointer points null, and the contents of the repetitive statement is that the dst pointer adds the value of the src pointer and increasing it one by one using the rear operator
	- Finally, add the null value to end of the dst pointer for notifying the end of string
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char *dst // char pointer
    char *src // char pointer
[Returns]       :
    Nothing
==================================================================*/
void
strcpy_p(char *dst, char *src)
{
    while (*src)  {
        (*dst++)=(*src++);
    }
    *dst = *src;
}
/*===============================================================
[Function Name] : void strcpy_a(char dst[], char src[])
[Description]   :
    - It is a function that receives the string dst and src as pointer parameters(same expression with dst[] and *dst) and copies the string from src to dst
	- Repeat the repetitive statement until the value of src array is null (\0), and add the value of src[i] to dst[i] and increase i one by one
	- break the repetitive statement if the value of src[i] is null
	- Finally, add the null value to end of the dst pointer for notifying the end of string
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char dst[] // char array => pointer
    char src[] // char array => pointer
[Returns]       :
    Nothing
==================================================================*/
void
strcpy_a(char dst[], char src[])
{
    int i;
    for (i = 0 ; src[i]!='\0' ; i++)
        dst[i] = src[i];
    dst[i] = src[i];
}

/*===============================================================
[Function Name] : void strcat_p(char *dst, char *src)
[Description]   :
    - It is a function that receives dst and src as pointer parameters as a character array and append the string from the src to the end of dst
	- When *dst is null, it is encounted the condition of breaking the repeat statement and then ++ operation run, the dst pointer points next of the null. To append the data from null, so do -- operation to point the null value
	- Place the src value in dst until src reaches null and increase both src and dst one by one.
	- Finally, add the null value to end of the dst pointer for notifying the end of string
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char *dst // char pointer
    char *src // char pointer
[Returns]       :
    Nothing
==================================================================*/
void
strcat_p(char *dst, char *src)
{
    while (*dst++)
        ;
    dst--;
    while (*src)  {
        *dst++ = *src++;
    }
    *dst = *src;
}
/*===============================================================
[Function Name] : void strcat_a(char dst[], char src[])
[Description]   :
    - It is a function that receives dst and src as pointer parameters as a character array(same expression with dst[] and *dst) and append the string from the src to the end of dst
    - When dst[i] is null, it is encounted the condition of breaking the repeat statement
    - Place the src[i] value in dst[i+j] until src[i] reaches null and increase j one by one.
	- the reason why the index of the dst is (i+j) is to append the value of src to the end of the dst
	- Finally, add the null value(src[j]) to end of the dst(dst[i+j]) for notifying the end of string
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char dst[] // char array => pointer
    char src[] // char array => pointer
[Returns]       :
    Nothing
==================================================================*/
void
strcat_a(char dst[], char src[])
{
    int i, j;
    for (i = 0 ; dst[i] != '\0' ; i++)
        ;
    for (j = 0 ; src[j] != '\0' ; j++)
        dst[i+j] = src[j];
    dst[i+j]=src[j];
}
/*===============================================================
[Function Name] : int strcmp_p(char *dst, char *src)
[Description]   :
    - It is a function that receives dst and src as pointer parameters as a character array and compare with dst and src.
    - Run the repeat statement until when the value of dst is same the value of src or when either dst or src encounts the end of the string. The content in the repeat statement is that increasing both dst pointer and src pointer.
    - If both dst and src encount the end of the string and are same, return 0 for the meaning of same string
    - Else if dst is larger than src, return the positive
	- Else if dst is smaller than src, return the negative
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char *dst // char pointer
    char *src // char pointer
[Returns]       :
	if *dst is same *src, return 0
	else if *dst is larger than *src, return positive
	else if *dst is smaller that *src, return negative
==================================================================*/
int strcmp_p(char *dst, char *src)
{
    while(*dst && *src && (*dst==*src)){
        *dst++;
        *src++;
    }
    if (*dst == *src)
        return 0;
    else if (*dst > *src)
        return 1;
    else if (*dst < *src)
        return -1;
}
/*===============================================================
[Function Name] : int strcmp_a(char dst[], char src[])
[Description]   :
    - It is a function that receives dst and src as pointer parameters as a character array(same expression both *dst and dst[]) and compare with dst and src.
    - Intitialize i into 0, Run the repeat statement by increasing i one by one until when dst[i] is null and src[i] is null. The content in the repeat statement is that continue if dst[i] is same src[i] or break if it is not same.
    - If both dst[i] and src[i] encount the end of the string and are same, return 0 for the meaning of same string
    - Else if dst[i] is larger than src[i], return the positive
    - Else if dst[i] is smaller than src[i], return the negative
[Input]         :
[Output]        :
[Call By]       :
    main()
[Calls]         :
    Nothiong
[Given]         :
    char dst[] // char array => pointer
    char src[] // char array => pointer
[Returns]       :
    if dst[i] is same src[i], return 0
    else if dst[i] is larger than src[i], return positive
    else if dst[i] is smaller that src[i], return negative
==================================================================*/
int strcmp_a(char dst[],char src[])
{
    int i;
    for (i=0; dst[i]!='\0'&&src[i]!='\0'; i++)
    {
        if (dst[i]==src[i])
            continue;
        break;
    }
    if (dst[i] == src[i])
        return 0;
    else if (dst[i] > src[i])
        return 1;
    else if (dst[i] < src[i])
        return -1;
}

/*===============================================================
  [Program Name] : string.c
  [Description] :
	- print the length of "Hello" when pointer and array
	- print the copies of "Hello" when pointer and array
	- print the string of appending "Hello" behind the str1 and str2 when pointer and array
	- print the result of comparing with two strings when pointer and array
  [Input] :
  [Output] :
	- int len1, len2 // the length of "Hello" when pointer and array
	- char str1[20], str2[20] // the copies of "Hello" when pointer and array
	- char str1[20], str2[20] // the string of appending "Hello" behind the str when pointer and array
	- int result, result1, result2 // the result of comparing with two strings when pointer
	- int res, res1, res2 // the result of comparing with two strings when array
  [Calls] :
	- int strlen_p(char *str)
	- int strlen_a(char str[])
	- void strcpy_p(char *dst, char *src)
	- void strcpy_a(char dst[], char src[])
	- void strcat_p(char *dst, char *src)
	- void strcat_a(char dst[], char src[])
	- int strcmp_p(char *dst,char *src)
	- int strcmp_a(char dst[],char src[])
  [특기사항] :
  ==================================================================*/

main()
{
    int		len1, len2;
    char	str1[20], str2[20];
    len1 = strlen_p("Hello");
    len2 = strlen_a("Hello");
    printf("strlen: p=%d, a=%d\n", len1, len2);
    strcpy_p(str1, "Hello");
    strcpy_a(str2, "Hello");
    printf("strcpy: p=%s, a=%s\n", str1, str2);
    strcat_p(str1, ", World!");
    strcat_a(str2, ", World!");
    printf("strcat: p=%s, a=%s\n", str1, str2);
    int result = strcmp_p("Hello","hello");
    int result1 = strcmp_p("hello","hello");
    int result2 = strcmp_p("hello","Hello");
    printf("result p= %d result1 p= %d result2 p= %d \n",result,result1,result2);
    printf("result diff p= %d \n",strcmp_p("he","hello"));
    printf("result diff2 p= %d \n",strcmp_p("hell","hel"));
    int res = strcmp_a("Hello","hello");
    int res1 = strcmp_a("hello","hello");
    int res2 = strcmp_a("hello","Hello");
    printf("res a= %d res1 a= %d res2 a= %d \n",res,res1,res2);
    printf("res diff a= %d \n",strcmp_a("he","hello"));
    printf("res diff2 a= %d \n",strcmp_a("hell","hel"));
}
//
// Created by 김수민 on 2022/11/01.
//
