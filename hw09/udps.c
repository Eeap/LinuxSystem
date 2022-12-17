#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "udp.h"


int	Sockfd;
/*===============================================================
[Function Name] : CloseServer()
[Description]   :
    - 이 함수는 sigint라는 시그널이 발생했을때 소켓을 종료하는 시그널 핸들러 함수
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    close() // socket을 닫는 함수
[Given]         :
[Returns]       :
=================================================================*/
void
CloseServer()
{
	close(Sockfd);
	printf("\nUDP Server exit.....\n");

	exit(0);
}

/*===============================================================
[Program Name] : udps.c
[Description]  :
    - 이 프로그램은 udp로 통신하는 서버 프로그램이다.
    - 먼저 서버쪽은 시그널 핸들러를 등록해서 소켓이 닫히도록 한다.
    - socket시스템 콜을 통해 IPv4로 udp방식으로 소켓을 하나 만든다. 그 다음 서버addr를 할당하고 서버의 주소를 네트워크 바이트 오더로 바꾸고 bind라는 함수를 통해서 소켓에 servaddr를 연결한다.
	- udp는 listen과 accept를 통해 클라이언트를 기다리지 않고 바로 recvfrom을 통해 클라이언트로부터 메시지를 전달 받는다. 이후 sendto로 recvfrom으로 전달받은 클라이언트의 주소로 reply메시지를 보낸다. sigint가 발생할때까지 이 작업을 반복한다.
[Input]        :
[Output]       :
[Calls]        :
    socket() // 소켓을 생성하는 함수
    bind() // 해당 소켓에 소켓주소를 연결하는 함수
    recvfrom() // 메시지를 받는 함수
	sendto() // 메시지를 보내는 함수
	close() // 소켓을 닫는 함수
    htonl() // host 주소를 network 바이트 오더로 long타입을 바꿔주는 함수
    htons() // host 주소를 network 바이트 오더로 short타입을 바꿔주는 함수
[특기사항]     :
==================================================================*/
main(int argc, char *argv[])
{
	int					cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;

	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	printf("UDP Server started.....\n");

	cliAddrLen = sizeof(cliAddr);
	while (1)  {
		if ((n = recvfrom(Sockfd, (char *)&msg, sizeof(msg), 
					0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
			perror("recvfrom");
			exit(1);
		}
		printf("Received request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (sendto(Sockfd, (char *)&msg, sizeof(msg),
					0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
			perror("sendto");
			exit(1);
		}
		printf("Replied.\n");
	}
}
