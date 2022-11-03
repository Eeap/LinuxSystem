#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct SumValue{
    int s;
    int sum;
} SUMVALUE, *SUM;
/*
 * typedef struct tTHREAD
{
   int a;
   int b;
}THREAD;

 void *thread_func(void* p)
 {
    THREAD* pp = (THREAD*)p;
    int k = pp->a;
    int j = pp->b;
    printf("k = %d, j = %d\n", k, j);

    return (void *)k+1;
 }


int main(int argc, char **argv)
{
   pthread_t th1;
   THREAD st;
   st.a = 1;
   st.b = 2;

   int res;
   int tid;

   tid = pthread_create(&th1, NULL, thread_func, (void *)&st);
   pthread_join(th1, (void **)&res);

   printf("result : %d\n", res);

   return 0;
}
 * */
/*===============================================================
[Function Name] : addSum(void *arg)
[Description]   :
	- arg로 받은 Sumvalue라는 구조체를 타입캐스팅해서 test에 저장한다
	- 그다음 내부 인자인 s(start point)를 idx에 저장해서 idx부터 idx+50까지 for문을 반복해서 구조체 안에 있는 sum에 저장한다
	- 1부터50까지 51부터 100까지 각각의 쓰레드가 각각의 구조체 내부의 sum에 저장을 했으면 쓰레드를 종료한다
[Input]         :
[Output]        :
[Call By]       :           
    Main()
[Calls]         :           
    pthread_exit() //thread를 종료하는 함수
[Given]         :
    void* arg // thread를 통해 넘겨받은 struct 구조체 포인터
[Returns]       :
==================================================================*/
void *
addSum(void* arg)
{

    SUMVALUE *test = (SUM)arg;
    int idx = test->s;

    for(int i=idx;i<(idx+50);i++){
        test->sum+=i;
    }
    pthread_exit(NULL);
}
/*===============================================================
[Program Name] : tadd.c
[Description]  : 
    - pthread_create를 통해 각각의 tid에 해당되게 addSum이라는 함수를 실행하는 쓰레드를 생성한다. 이때 넘겨주는 인자는 미리 struct로 선언해서 start지점과 sum을 설정한다.
	- pthread_join이라는 함수를 통해 tid1과 tid2의 쓰레드가 끝나길 기다린다.
	- 이후 각각의 구조체 arg1, arg2에 저장되어있는 sum을 합쳐서 1부터 100까지의 결과값을 출력한다
[Input]        :
[Output]       :
[Calls]        :            
    pthread_create() // thread를 만드는 함수로 tid와 수행할 함수와 파라미터를 받아서 쓰레드를 생성한다
    pthread_join() //해당 tid값을 가진 thread가 종료될때까지 기다린다.
[특기사항]     : 
==================================================================*/
int main()
{
    pthread_t   tid1, tid2;
    int r1;
    int r2;
    SUM arg1 = (SUM) malloc(sizeof(SUMVALUE));
    arg1->s=1;
    arg1->sum=0;
    SUM arg2 = (SUM) malloc(sizeof(SUMVALUE));
    arg2->s=51;
    arg2->sum=0;

    if (pthread_create(&tid1, NULL, (void *)addSum, (void *)arg1) < 0)  {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, (void *)addSum, (void *)arg2) < 0)  {
        perror("pthread_create");
        exit(1);
    }

    printf("Threads created: tid=%d, %d\n", tid1, tid2);

    if (pthread_join(tid1, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(tid2, NULL) < 0)  {
        //int st;
        //pthread_join(tid2,(void **)&st);
        perror("pthread_join");
        exit(1);
    }
    int sum = arg1->sum+arg2->sum;
    printf("Threads terminated: tid=%d, %d\n sum = %d\n", tid1, tid2,sum);

}