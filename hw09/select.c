#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include "select.h"
#include <pthread.h>

int	TcpSockfd;
int	UdpSockfd;
int	UcoSockfd;
int	UclSockfd;
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
	close(TcpSockfd);
	close(UdpSockfd);
	close(UcoSockfd);
	close(UclSockfd);
	if (remove(UNIX_STR_PATH) < 0)  {
		perror("remove");
	}
	if (remove(UNIX_DG_PATH) < 0)  {
		perror("remove");
	}

	printf("\nServer daemon exit.....\n");

	exit(0);
}
/*===============================================================
[Function Name] : MakeTcpSocket()
[Description]   :
    - 이 프로그램은 tcp로 통신하는 서버 함수이다.
    - socket시스템 콜을 통해 IPv4로 tcp방식으로 소켓을 하나 만든다. 그 다음 서버addr를 할당하고 서버의 주소를 네트워크 바이트 오더로 바꾸고 bind라는 함수를 통해서 소켓에 servaddr를 연결한다. 그 후 listen을 통해서 클라이언트 소켓의 connect를 기다린다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    socket() // 소켓을 생성하는 함수
    bind() // 해당 소켓에 소켓주소를 연결하는 함수
    listen() // 커넥션을 기다리는 함수
    htonl() // host 주소를 network 바이트 오더로 long타입을 바꿔주는 함수
    htons() // host 주소를 network 바이트 오더로 short타입을 바꿔주는 함수
[Given]         :
[Returns]       :
=================================================================*/
void
MakeTcpSocket(void *dummy)
{
	struct sockaddr_in	servAddr;

	if ((TcpSockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(TcpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(TcpSockfd, 5);
    pthread_exit(NULL);
}
/*===============================================================
[Function Name] : MakeUdpSocket()
[Description]   :
   - 이 프로그램은 udp로 통신하는 서버 함수이다.
    - socket시스템 콜을 통해 IPv4로 udp방식으로 소켓을 하나 만든다. 그 다음 서버addr를 할당하고 서버의 주소를 네트워크 바이트 오더로 바꾸고 bind라는 함수를 통해서 소켓에 servaddr를 연결한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    socket() // 소켓을 생성하는 함수
    bind() // 해당 소켓에 소켓주소를 연결하는 함수
    htonl() // host 주소를 network 바이트 오더로 long타입을 바꿔주는 함수
    htons() // host 주소를 network 바이트 오더로 short타입을 바꿔주는 함수
[Given]         :
[Returns]       :
=================================================================*/
void
MakeUdpSocket(void *dummy)
{
	struct sockaddr_in	servAddr;

	if ((UdpSockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	if (bind(UdpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}
    pthread_exit(NULL);
}

void
MakeUcoSocket(void *dummy)
{
	struct sockaddr_un	servAddr;
	int					servAddrLen;

	if ((UcoSockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sun_family = PF_UNIX;
	strcpy(servAddr.sun_path, UNIX_STR_PATH);
	servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

	if (bind(UcoSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(UcoSockfd, 5);
    pthread_exit(NULL);
}

void
MakeUclSocket(void *dummy)
{
	struct sockaddr_un	servAddr;
	int					servAddrLen;

	if ((UclSockfd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sun_family = PF_UNIX;
	strcpy(servAddr.sun_path, UNIX_DG_PATH);
	servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

	if (bind(UclSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
		perror("bind");
		exit(1);
	}
    pthread_exit(NULL);

}
/*===============================================================
[Function Name] : ProcessTcpRequest()
[Description]   :
    - accept를  통해 클라이언트와 연결하고 read를 통해 클라이언트가 보낸 메시지를 읽고 write를 통해 reply를 한뒤 연결 소켓을 close한다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    accept() // 커넥션 소켓을 생성하는 함수
    read() // 소켓에 오는 메시지를 읽어오는 함수
    write() // 소켓에 메시지를 쓰는 함수
    close() // 소켓을 닫는 함수
[Given]         :
[Returns]       :
=================================================================*/
void
ProcessTcpRequest(void *dummy)
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr;
	MsgType				msg;

	cliAddrLen = sizeof(cliAddr);
	newSockfd = accept(TcpSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
	if (newSockfd < 0)  {
		perror("accept");
		exit(1);
	}
		
	if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received TCP request: %s.....", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Replied.\n");

	close(newSockfd);
    pthread_exit(NULL);
}
/*===============================================================
[Function Name] : ProcessUdpRequest()
[Description]   :
    - accept를 통해 클라이언트를 기다리지 않고 바로 recvfrom을 통해 클라이언트로부터 메시지를 전달 받는다. 이후 sendto로 recvfrom으로 전달받은 클라이언트의 주소로 reply메시지를 보낸다.
[Input]         :
[Output]        :
[Call By]       :
[Calls]         :
    recvfrom() // 메시지를 받는 함수
    sendto() // 메시지를 보내는 함수
[Given]         :
[Returns]       :
=================================================================*/
void
ProcessUdpRequest(void *dummy)
{
	int					cliAddrLen, n;
	struct sockaddr_in	cliAddr;
	MsgType				msg;

	cliAddrLen = sizeof(cliAddr);
	if ((n = recvfrom(UdpSockfd, (char *)&msg, sizeof(msg), 
				0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received UDP request: %s.....", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (sendto(UdpSockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Replied.\n");
    pthread_exit(NULL);
}

void
ProcessUcoRequest(void *dummy)
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_un	cliAddr;
	MsgType				msg;

	cliAddrLen = sizeof(cliAddr);
	newSockfd = accept(UcoSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
	if (newSockfd < 0)  {
		perror("accept");
		exit(1);
	}
		
	if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received UNIX-domain CO request: %s.....", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Replied.\n");

	close(newSockfd);
    pthread_exit(NULL);
}

void
ProcessUclRequest(void *dummy)
{
	int					cliAddrLen, n;
	struct sockaddr_un	cliAddr;
	MsgType				msg;

	cliAddrLen = sizeof(cliAddr);
	if ((n = recvfrom(UclSockfd, (char *)&msg, sizeof(msg), 
				0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received UNIX-domain CL request: %s.....", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (sendto(UclSockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Replied.\n");
	pthread_exit(NULL);
}
/*===============================================================
[Program Name] : select.c
[Description]  :
    - 이 프로그램은 select함수를 이용해서 여러 개의 소켓 요청을 synchronous하게 처리하는 프로그램이다.
    - 각각의 소켓을 만들고 FD_SET을 통해 소켓을 등록하고 FD_ISSET을 통해 해당 소켓 요청이 오면 처리한다.
[Input]        :
[Output]       :
[Calls]        :
    signal() // 시그널이 오면 해당 시그널 핸들러를 호출하는 함수
    FD_ZERO() // fdset을 clear하는 함수
    FD_SET() // fdset에 해당 소켓을 등록하는 함수
    FD_ISSET() // fdset에 해당 소켓이 set됐는지 확인하는 함수
    select() // 여러 개의 소켓 요청을 synchronous하게 처리하는 함수
[특기사항]     :
==================================================================*/
main(int argc, char *argv[])
{
	fd_set	fdvar;
	int		count;
	pthread_t tid1,tid2,tid3,tid4,tid5,tid6,tid7,tid8;
	signal(SIGINT, CloseServer);
	if (pthread_create(&tid1,NULL,(void *)MakeTcpSocket,(void *)NULL)<0){
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&tid2,NULL,(void *)MakeUdpSocket,(void *)NULL)<0){
        perror("pthread_create");
        exit(1);
    }
	if (pthread_create(&tid3,NULL,(void *)MakeUcoSocket,(void *)NULL)<0){
        perror("pthread_create");
        exit(1);
    }
	if (pthread_create(&tid4,NULL,(void *)MakeUclSocket,(void *)NULL)<0){
        perror("pthread_create");
        exit(1);
    }
	
	printf("Server daemon started.....\n");

	while (1)  {
		FD_ZERO(&fdvar);
		FD_SET(TcpSockfd, &fdvar);
		FD_SET(UdpSockfd, &fdvar);
		FD_SET(UcoSockfd, &fdvar);
		FD_SET(UclSockfd, &fdvar);
		if ((count = select(10, &fdvar, (fd_set *)NULL, (fd_set *)NULL, 
			(struct timeval *)NULL)) < 0)  {
			perror("select");
			exit(1);
		}
		while (count--)  {
			if (FD_ISSET(TcpSockfd, &fdvar))  {
				if (pthread_create(&tid5,NULL,(void *)ProcessTcpRequest,(void *)NULL)<0){
        			perror("pthread_create");
        			exit(1);
    			}
                if (pthread_join(tid5,NULL)<0) {
                    perror("pthread_join");
                    exit(1);
                }
			}
			else if (FD_ISSET(UdpSockfd, &fdvar))  {
                if (pthread_create(&tid6,NULL,(void *)ProcessUdpRequest,(void *)NULL)<0){
                    perror("pthread_create");
                    exit(1);
                }
                if (pthread_join(tid6,NULL)<0) {
                    perror("pthread_join");
                    exit(1);
                }
			}
			else if (FD_ISSET(UcoSockfd, &fdvar))  {
                if (pthread_create(&tid7,NULL,(void *)ProcessUcoRequest,(void *)NULL)<0){
                    perror("pthread_create");
                    exit(1);
                }
                if (pthread_join(tid7,NULL)<0) {
                    perror("pthread_join");
                    exit(1);
                }
			}
			else if (FD_ISSET(UclSockfd, &fdvar))  {
                if (pthread_create(&tid8,NULL,(void *)ProcessUclRequest,(void *)NULL)<0){
                    perror("pthread_create");
                    exit(1);
                }
				if (pthread_join(tid8,NULL)<0) {
					perror("pthread_join");
					exit(1);
				}
			}
		}
	}
	if (pthread_join(tid1,NULL)<0) {
		perror("pthread_join");
		exit(1);
	}
    if (pthread_join(tid2,NULL)<0) {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(tid3,NULL)<0) {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(tid4,NULL)<0) {
        perror("pthread_join");
        exit(1);
    }
}
 
