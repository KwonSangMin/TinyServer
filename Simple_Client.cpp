#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 1024
#define PORT 2802
#define SERVERADDR "localhost"
int main()
{
	int server_fd,client_fd;
	struct sockaddr_in server_addr;
	pid_t pid;
	socklen_t size;
	client_fd=socket(PF_INET,SOCK_STREAM,0);
	if(client_fd==-1)
	{
		printf("SOCKET ERROR\n");
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=PF_INET;
	server_addr.sin_port=htons(PORT);
	inet_aton(SERVERADDR,&server_addr.sin_addr);
	int ret = connect(client_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret==-1)
		printf("CONNECT Return -1\n");
	char* buffer[BUF_SIZE];
	memset(buffer,0,1024);
	printf("WAITING RECV FROM SERVER\n");
  int recv_length=0;
	while(recv_length<30)//클라이언트와 서버가 연결될 경우 서버의 자식 프로세스가 클라이언트에게 메세지를 보낸다. 하지만 네트워크 상황에따라 언제 패킷이 도착할지 알수없다. 또한, 클라이언트에서는 서버가 얼마만큼의 데이터를 보내는지 알 수 없기 때문에 기존에 데이터양을 합의하거나, 전송 데이터 크기를 미리 전달해주어야한다. 그이후에 원하는 데이터 크기만큼 수신이 될 때까지 무한루프를 돌려서 계속해서 패킷을 읽어오도록 해야한다.
  {
    recv_length+=recv(client_fd,buffer,30,0);
  }
  printf("Client :: Message From Server -> %s\n",buffer);
	send(client_fd,"HI I AM A CHILD",30,0);
	close(client_fd);
}
