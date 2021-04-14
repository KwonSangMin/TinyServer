#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <thread>
using namespace std;
int main()
{
        struct sockaddr_in server_addr, client_addr;
        int server_fd, client_fd;
        memset(&server_addr,0,sizeof(server_addr));
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
        printf("Server :: Wating For Connecting With Port = %d\n",2802);
        while(1)
        {
                client_fd=accept(server_fd,(struct sockaddr *)&client_addr,(socklen_t*)&size);
                if(client_fd<0)
                {
                        printf("Aceept Error\n");
                        return 0;
                }
                inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,buffer, 1024);
                printf("Server :: Now %s Client Connected \n",buffer);

        }
        return 0;
}
~
