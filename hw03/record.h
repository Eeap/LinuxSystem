#define	SMAX	20
#define	NMAX	10
#define	DMAX	15


//Record라는 구조체를 typedef로 선언한 h파일. 필드에는 stud,num,dept이 있다.
typedef struct {
    char	stud[SMAX];
    char	num[NMAX];
    char	dept[DMAX];
} Record;
