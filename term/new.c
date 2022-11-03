#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
main(){
	DIR *dp;
	struct dirent *dep;
	struct stat buf;
	if((dp=opendir("."))<0){
		perror("opendir");
		exit(1);
	}	
	int time;
	char *filename;
	while(dep=readdir(dp)){
		if(lstat(dep->d_name,&buf)<0){
			perror("stat");
			exit(1);
		}
		if(strcmp(dep->d_name,".")==0 || strcmp(dep->d_name,"..")==0)
		{continue;}
		if (buf.st_mtime>time){
			time=buf.st_mtime;
			filename=dep->d_name;
		}
		
	}
	printf("%s\n",filename);

}
