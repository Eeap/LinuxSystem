#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"


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
	printf("\nTCP Server exit.....\n");

	exit(0);
}

/*===============================================================
[Program Name] : tcps.c
[Description]  :
	- 이 프로그램은 tcp로 통신하는 서버 프로그램이다.
	- 먼저 서버쪽은 시그널 핸들러를 등록해서 소켓이 닫히도록 한다.
	- socket시스템 콜을 통해 IPv4로 tcp방식으로 소켓을 하나 만든다. 그 다음 서버addr를 할당하고 서버의 주소를 네트워크 바이트 오더로 바꾸고 bind라는 함수를 통해서 소켓에 servaddr를 연결한다. 그 후 listen을 통해서 클라이언트 소켓의 connect를 기다린다.
	- accept를  통해 클라이언트와 연결하고 read를 통해 클라이언트가 보낸 메시지를 읽고 write를 통해 reply를 한뒤 연결 소켓을 close한다. 이 작업을 sigint 시그널이 오기전까지 while문으로 반복한다.
[Input]        :
[Output]       :
[Calls]        :
	socket() // 소켓을 생성하는 함수
	bind() // 해당 소켓에 소켓주소를 연결하는 함수
	listen() // 커넥션을 기다리는 함수
	accept() // 커넥션 소켓을 생성하는 함수
	read() // 소켓에 오는 메시지를 읽어오는 함수
	write() // 소켓에 메시지를 쓰는 함수
	close() // 소켓을 닫는 함수
    htonl() // host 주소를 network 바이트 오더로 long타입을 바꿔주는 함수
    htons() // host 주소를 network 바이트 오더로 short타입을 바꿔주는 함수
[특기사항]     :
==================================================================*/
main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;
	int pid;
	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5);

	printf("TCP Server started.....\n");

	cliAddrLen = sizeof(cliAddr);
	while (1)  {
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
			perror("accept");
			exit(1);
		}
		
		if ((pid = fork())< 0 ) {
			perror("fork");
			exit(1);
		}
		else if (pid==0) {
			if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
            	perror("read");
            	exit(1);
        	}
        	printf("Received request: %s.....", msg.data);

        	msg.type = MSG_REPLY;
        	sprintf(msg.data, "This is a reply from %d.", getpid());
        	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
            	perror("write");
            	exit(1);
        	}
        	printf("Replied.\n");

        	usleep(10000);
        	close(newSockfd);
		}
		
	}
}
