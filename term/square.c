#include <stdio.h>
#include <stdlib.h>


main(int argc, char *argv[])
{
	for (int i=1;i<argc;i++){
		int num = atoi(argv[i]);
		printf("%d\n",num*num);
	}
	
}

