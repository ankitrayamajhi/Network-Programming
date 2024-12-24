#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define IP "192.168.18.5"
#define PORT 9999

int main(int argc, char *argv[])
{
  
    char hello[]="Hello Cosmos";
    char buff[100];
    int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(client_fd<0) {
        perror("socket creation failed ");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET; // IPv4 family 
    server_addr.sin_addr.s_addr = inet_addr(IP);
    server_addr.sin_port = htons(PORT);

    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    int addr_len = sizeof(server_addr);
    int connect_server = connect(client_fd,( struct sockaddr *)&server_addr, addr_len);
     
    if (connect_server == -1) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    printf("client message to server:  %s \n",hello);

    write(client_fd, hello,sizeof(hello));

    read(client_fd, buff, 100);

    printf("server response: %s",buff);



    return 0;
}

