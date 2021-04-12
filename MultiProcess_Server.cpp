#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 #define PORT 2802
 #define BUF_SIZE 1024
 void init_chat(int client_fd, char* buffer)
 {
    int recv_length=0;
    sprintf(buffer,"HI Client I Am Server With Pid = %d\n" getpid());
    send(client_fd,buffer,30,0);
    while(recv_length<30)
    {
      recv_length+=recv(client_fd,buffer,30,0);
    }
    printf("Server :: Message From Client -> %s\n",buffer);
 }
 int main()
 {
    int server_fd, client_fd;
    struct sockaddr_in host_addr, client_addr;
    socklent_t size;
    char buffer[BUF_SIZE];
    server_fd=socket(PF_INET,SOCK_STREAM,0);
    if(server_fd==-1)
    {
      printf("SOCKET FUNCTION RETURN -1\n");
      return 0;
    }
    host_addr.sin_family=AF_INET;
    host_addr.sin_port=htons(PORT);//host endian 에서 네트워크의 엔디안인 BIG ENDIAN으로 변경
    host_addr.sin_addr_.s_addr=htons(INADDR_ANY);//Host Endian에서 네트워크 ENDIAN으로 변경해준다, INADDR_ANY는 여러 NIC로 들어오는 모든 접근을 탐지하고 받아오도록해준다.
    if(bind(server_fd,(struct sockaddr*)&host_addr,sizeof(struct sockaddr)==-1)//bind 함수와 sockaddr은 IP 프로토콜 이외에 다른 통신 프로토콜에도 사용되는 범용 구조체이다. 해당 구조체는 IP통신용 구조체인 sockaddr_in(패딩포함)과 동일한 크기를 가지고 있다.
    {
      printf("Bind Function Return -1\n");
      return 0;
    }
    if(listen(server_fd,10)==-1)//listen 함수는 해당 소켓이 외부 접속을 탐색하도록 만들어준다. 두 번째 parameter는 대기 queue 사이즈를 의미한다.
    {
      printf("Listen Function return -1\n");
    }
    size=sizeof(client_addr);
    while(1)
    {
      printf("Server Listening Process is Listening for connect : PID = %d \n",getpid());
      client_fd=accept(server_fd,(struct sockaddr*)&client_addr, &size);//accept함수 또한 범용 프로토콜임으로 sockaddr_in 구조체를 형변환을 통해 넘겨줘야한다 정상 수행할 경우 연결된 Client에 할당된 fd를 반환한다.
      pid_t IsParent=fork();
      if(IsParent==0)//Child
      {
        close(server_fd);//server socket은 listen할 때 사용되는 소켓이다. listen은 부모 프로세스가 담당하므로 child프로세스는 즉시 닫아주도록 한다.
        init_chat(client_fd,buffer);
        close(client_fd);// 대화가 끝나면 해당 소켓을 닫아준다.
        return 0;
      }
      else
      {
        close(client_fd);//자식 프로세스에게 작업을 위임햇으므로 즉시 소켓을 닫아준다.
      }
    }
    
    
    
