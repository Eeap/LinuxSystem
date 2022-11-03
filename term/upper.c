#include <stdio.h>

void
strupper(char str[]){
	int i;
	for (i=0;str[i]!='\0';i++){
		if (str[i]>=97 && str[i]<=122)
		{
			str[i]-=32;
		}
	}
	printf("%s\n",str);
}

main(){
	char text[] = "hello, world!";
	strupper(text);
}
