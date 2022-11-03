#include <stdio.h>
#include <pthread.h>


/*===============================================================
[Function Name] : PrintMsg(char *msg)
[Description]   : msg를 출력하고 thread를 종료하는 함수
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
    pthread_exit() //thread를 종료하는 함수
[Given]         :
    char *msg //출력할 문자열
[Returns]       :
==================================================================*/
void
PrintMsg(char *msg)
{
    printf("%s", msg);

    pthread_exit(NULL);
}
/*===============================================================
[Program Name] : thread.c
[Description]  : 
	- pthread_create라는 함수를 통해 PrintMsg 함수를 수행하는 쓰레드를 tid1, tid2로 두개를 만든다(attr는 NULL 파라미터는 각각 msg1,msg2)
	- pthread_join이라는 함수를 통해 tid1과 tid2의 쓰레드가 끝나길 기다린다.
[Input]        :
[Output]       :
[Calls]        :            
	pthread_create() // thread를 만드는 함수로 tid와 수행할 함수와 파라미터를 받아서 쓰레드를 생성한다
	pthread_join() //해당 tid값을 가진 thread가 종료될때까지 기다린다.
[특기사항]     : 
==================================================================*/
main()
{
    pthread_t	tid1, tid2;
    char		*msg1 = "Hello, ";
    char		*msg2 = "World!\n";

    /* Thread ID: tid1, Thread function: PrintMsg, Thread argument: msg1 */
    if (pthread_create(&tid1,NULL,(void *)PrintMsg,(void *)msg1)<0)  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, (void *)PrintMsg, (void *)msg2) < 0)  {
        perror("pthread_create");
        exit(1);
    }

    printf("Threads created: tid=%d, %d\n", tid1, tid2);

    /* Wait for tid1 to exit */
    if (pthread_join(tid1,NULL)<0)  {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(tid2, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    printf("Threads terminated: tid=%d, %d\n", tid1, tid2);
}