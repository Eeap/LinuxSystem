#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
main(int argc, char *argv[]){
    FILE *fp;
    int ch,cnt=0;
    if(argc!=2)
    {
        perror("error");
        exit(1);
    }
    if((fp=fopen(argv[1],"rt"))==NULL){
        perror("file");
        exit(1);
    }
	int check;
	int wasC=1;
    while((ch=fgetc(fp))!=EOF){
		check = isspace(ch) ? 1:0;
		if(check == wasC)
			continue;	
		else if(check){
			wasC=1;
			cnt+=1;	
		}
		else{
			wasC=0;
		}
    }
    printf("%d\n",cnt);
    fclose(fp);

}
