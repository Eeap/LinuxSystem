#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "udp.h"

/*===============================================================
[Program Name] : udpc.c
[Description]  :
    - 이 프로그램은 udp로 통신하는 클라이언트 프로그램이다.
    - socket시스템 콜을 통해 IPv4로 udp방식으로 소켓을 하나 만든다. 그 다음 servaddr를 할당하고 주소를 네트워크바이트 오더로 바꾼다.
	- sendto로 서버에 메시지를 보내고 recvfrom으로 서버로부터 reply 메시지를 받고 소켓을 종료한다.
[Input]        :
[Output]       :
[Calls]        :
    socket() // 소켓을 생성하는 함수
    recvfrom() // 메시지를 받는 함수
    sendto() // 메시지를 보내는 함수
	close() // 소켓을 닫는 함수
    inet_addr() // dot주소를 32bit주소로 바꿔주는 함
	htons() // host 주소를 network 바이트 오더로 short타입을 바꿔주는 함수
[특기사항]     :
==================================================================*/
main(int argc, char *argv[])
{
	int					sockfd, n, peerAddrLen;
	struct sockaddr_in	servAddr, peerAddr;
	MsgType				msg;

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
	if (sendto(sockfd, (char *)&msg, sizeof(msg), 
			0, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Sent a request.....");
		
	peerAddrLen = sizeof(peerAddr);
	if ((n = recvfrom(sockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&peerAddr, &peerAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received reply: %s\n", msg.data);

	close(sockfd);
}
