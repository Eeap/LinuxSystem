#include <stdio.h>


main(){
	int i,cnt=10;
	
	while(cnt){
		for (i=1;i<cnt;i++){
			printf("%d ",i);
		}
		cnt--;
		printf("\n");
	}
}
