#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
main(int argc, char *argv[]){
	if(argc!=2){
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
	}
	int size = atoi(argv[1]);
	DIR *dp;
	struct dirent *dep;
	struct stat buf;
	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(1);
	}
	while(dep=readdir(dp)){
		if (lstat(dep->d_name,&buf)<0){
			perror("lstat");
			exit(1);
		}
		if(strcmp(dep->d_name,".")==0 || strcmp(dep->d_name,"..")==0)
			continue;
		if(buf.st_size >=size)
			printf("%s\n",dep->d_name);
	}

}
