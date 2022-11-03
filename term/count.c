#include <stdio.h>


main(int argc, char *argv[]){
	FILE *fp;
	int ch,cnt=0;
	if(argc!=3)
	{
		perror("error");
		exit(1);
	}
	if((fp=fopen(argv[1],"rt"))==NULL){
		perror("file");
		exit(1);
	}
	while((ch=fgetc(fp))!=EOF){
		if(ch-*argv[2]==0){
			cnt+=1;
		}
	}
	printf("%d\n",cnt);
	fclose(fp);
	
}
