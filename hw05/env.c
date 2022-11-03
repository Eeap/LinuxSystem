#include <stdio.h>
/*===============================================================
[Program Name] : env.c
[Description]  :
	- 이 파일은 환경변수를 출력하는 파일이다.
	- extern 변수를 이용해서 다른파일에 저장되어 있는 전역 변수를 이용할 수 있지만 세번째 파라미터로 받은 envp를 통해서 환경 변수를 받아올 수 있다.
[Input]        :
	int argc // argv의 개수
	char *argv[] // 입력받은 argv
	char *envp[] //파라미터로 환경변수를 받아오는 경우
[Output]       :
[Calls]        :
[특기사항]     :
==================================================================*/
main(int argc, char *argv[], char *envp[])
{
    int			i;
    char		**p;
    extern char	**environ;

    printf("List command-line arguments\n");
    for (i = 0 ; i < argc ; i++)  {
        printf("%s\n", argv[i]);
    }

    printf("\n");
    printf("List environment variables from environ variable\n");
#if 1
    for (i = 0 ; environ[i] != NULL ; i++)  {
        printf("%s\n", environ[i]);
    }
#else
    for (p = environ ; *p != NULL ; p++)  {
		printf("%s\n", *p);
	}
#endif

    printf("\n");
    printf("List environment variables from envp variable\n");
#if 1
    for (i = 0 ; envp[i] != NULL ; i++)  {
        printf("%s\n", envp[i]);
    }
#else
    for (p = envp ; *p != NULL ; p++)  {
		printf("%s\n", *p);
	}
#endif