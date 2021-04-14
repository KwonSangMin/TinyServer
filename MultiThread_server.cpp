#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <thread>
using namespace std;
char MessageBuffer[1024];
void write(int);
void read();
int main()
{
        struct sockaddr_in server_addr, client_addr;
        int server_fd, client_fd;
        memset(&server_addr,0,sizeof(server_addr));
        server_fd=socket(AF_INET,SOCK_STREAM,0);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(2802);
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(server_fd,(struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
        {
                printf("Bind Error\n");
                return 0;
        }
        if(listen(server_fd,10)==-1)
        {
                printf("Listen Error\n");
                return 0;
        }
        char buffer[1024];
        auto size=sizeof(client_addr);
        while(1)
        {
                printf("Server :: Wating For Connecting With Port = %d\n",2802);
                client_fd=accept(server_fd,(struct sockaddr *)&client_addr,(socklen_t*)&size);
                if(client_fd<0)
                {
                        printf("Aceept Error\n");
                        return 0;
                }
                inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,buffer, 1024);
                printf("Server :: Now %s Client Connected \n",buffer);
                thread A(write,client_fd);
                A.detach();
        }
        return 0;
}
void write(int client_fd)
{
        int recv_length=0;
        char buffer[1024];
        int M_L_C;
        memset(&buffer,0,1024);
        while(recv_length<4){recv_length+=recv(client_fd,&buffer,4,0);}
        M_L_C=*(int*)buffer;
        printf("Server :: Client_Message_Length = %d\n",M_L_C);
        recv_length=0;
        memset(&buffer,0,1024);
        while(recv_length<M_L_C)
        {
                recv_length+=recv(client_fd,&buffer,M_L_C,0);
        }
        printf("Server :: Client_Message -> %s\n",buffer);
        send(client_fd,"We Recieved Your Message\n",30,0);
        //while(recv_length<)
}
