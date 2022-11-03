#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>

main(int argc,char *argv[])
{
	int pid;
	
	if (argc!=2){
		exit(1);
	}
	char *v[]={"wc","-w",argv[1],NULL};
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	else if(pid==0){
		if(execvp("wc",v)<0){
			perror("execvp");
			exit(1);
		}
	}
	else{
		wait(NULL);
	}
	
}

