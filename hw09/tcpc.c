#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"
/*===============================================================
[Program Name] : tcpc.c
[Description]  :
    - 이 프로그램은 tcp로 통신하는 클라이언트 프로그램이다.
    - socket시스템 콜을 통해 IPv4로 tcp방식으로 소켓을 하나 만든다. 그 다음 servaddr를 할당하고 주소를 네트워크바이트 오더로 바꾼다.
	- connect를 통해 서버와 연결하고 write를 통해 메시지를 쓰고 read를 통해 reply받은 메시지를 읽고 종료한다.
[Input]        :
[Output]       :
[Calls]        :
    socket() // 소켓을 생성하는 함수
    connect() // 서버와 연결하는 함수 
    read() // 소켓에 오는 메시지를 읽어오는 함수
    write() // 소켓에 메시지를 쓰는 함수
    close() // 소켓을 닫는 함수
    htons() // host 주소를 network 바이트 오더로 short타입을 바꿔주는 함수
    inet_addr() // dot주소를 32bit주소로 바꿔주는 함
[특기사항]     :
==================================================================*/

main(int argc, char *argv[])
{
	int					sockfd, n;
	struct sockaddr_in	servAddr;
	MsgType				msg;

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}

	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
	if (write(sockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Sent a request.....");
		
	if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received reply: %s\n", msg.data);

	close(sockfd);
}
