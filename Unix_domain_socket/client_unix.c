#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<errno.h>
#define PATH "/home/ankit/Documents/7th - Sem/Network programming/Lab/unix.txt"

int main(int arg, char** argv)
{
        int fd;
        fd=socket(AF_UNIX, SOCK_STREAM, 0);
        if(fd>0)
        printf("ENd point created\n");
        struct sockaddr_un client;
        memset(&client,0,sizeof(struct sockaddr_un));
        client.sun_family=AF_UNIX;
        strncpy(client.sun_path, PATH, sizeof(client.sun_path) - 1);
        int c=connect(fd,(struct sockaddr*)&client,sizeof(struct sockaddr_un));
        if(c == -1)
        {
                printf("Error in Connecting to server[%d]\n",errno);
        }

        const char* sendmsg="Hello this is UNIX DOmain Client";
        char recvBuff[100];
        ssize_t s=send(fd,sendmsg,strlen(sendmsg),0);
        printf("Message send to  UNIX-Server[%s]msg len[%d]\n",sendmsg,s);
        ssize_t r=recv(fd,recvBuff,100,0);
        printf("Message Received from  UNIX-Server[%s]msg len[%d]\n",recvBuff,r);
        close(fd);
        return 0;
}

