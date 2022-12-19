#define MY_ID           11

#define SERV_TCP_PORT   (7000 + MY_ID)
#define SERV_HOST_ADDR  "127.0.0.1"

#define MSG_REQUEST     1
#define MSG_REPLY       2


typedef struct  {
    int     type;
    int data;
}
    MsgType;
