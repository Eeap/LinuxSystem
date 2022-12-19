#define	MY_ID		11
#define	SHM_KEY		(0x9000 + MY_ID)
#define	SHM_MODE	(SHM_R | SHM_W | IPC_CREAT)
#define EMPTY_SEM_KEY   (0x1000 + MY_ID)
#define FULL_SEM_KEY    (0x2000 + MY_ID)
typedef struct  {
    int     data;
}
    ItemType;

typedef struct  {
    int   data;
}
    BoundedBufferType;

#define SHM_SIZE    sizeof(BoundedBufferType)
