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
        char buffer[BUF_SIZE];
        memset(buffer,0,1024);
        printf("WAITING RECV FROM SERVER\n");
        /*int recv_length=0;
        while(recv_length<30)
        {
          recv_length+=recv(client_fd,buffer,30,0);
        }
        printf("Client :: Message From Server -> %s\n",buffer);*/

        scanf("%s", buffer);
        int buffersize= sizeof(buffer);
        printf("buffersize=%d\n",buffersize);
        send(client_fd,(char*)&buffersize,4,0);
        send(client_fd,buffer,1024,0);
        int recv_length=0;
        while(recv_length<30)
        {
          memset(&buffer,0,1024);
          recv_length+=recv(client_fd,buffer,30,0);
        }
        printf("Send Finished\n");
        close(client_fd);
}
