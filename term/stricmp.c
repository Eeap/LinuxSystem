int stricmp_p(char *dst, char *src)
{
    while(*dst && *src){
		if(*dst>=65 && *dst<=90){
			*dst+=32;
		}
		if(*src>=65 && *src<=90){
            *src+=32;
        }
		if(*dst == *src){
			*dst++;
        	*src++;
		}
    	else{
			break;
		}
	}
    if (*dst == *src)
        return 0;
    else if (*dst > *src)
        return 1;
    else if (*dst < *src)
        return -1;
}
void main()
{
	char str1[] = "Hello";
	char str2[] = "hello";
	char str3[] = "World!";
	printf("%d : %d\n", stricmp_p(str1, str2),stricmp_p(str1, str3));
}
