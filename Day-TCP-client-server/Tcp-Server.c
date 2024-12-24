#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define PORT 9999
#define IP "192.168.18.5"

int main() {
    printf("Welcome to NP-Socket Lab-1\n");
    char readBuffer[100];
    int fd, confd;
    char str[100];
    struct sockaddr_in server, client;
    char sendBuff[1024];
    time_t ticks;

    // Creating the socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket created with descriptor [%d]\n", fd);

    // Initializing server structure
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    // server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    // Binding the socket
    if (bind(fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("bind");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Converting IP address to a readable format
    inet_ntop(AF_INET, &server.sin_addr, str, INET_ADDRSTRLEN);

    // Listening on the socket
    if (listen(fd, 5) < 0) {
        perror("listen");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Program Listening on IP [%s] and PORT [%d]\n", str, PORT);

    // Infinite loop to handle connections continuously
    while (1) {
        socklen_t len = sizeof(client);
        confd = accept(fd, (struct sockaddr*)&client, &len);
        if (confd < 0) {
            perror("accept");
            continue; // Continue to the next iteration if accept fails
        }

        // Getting the current time
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        printf("Sending time: %s", sendBuff);

        int i = 0;
      i =  read(confd, readBuffer, 100);
      printf("Number of byte received %d{%s}\n",i,readBuffer);

        // Sending time to the client
        write(confd, sendBuff, strlen(sendBuff));

        // Closing the connection with the client
        close(confd);
    }

    // Closing the main socket (this code will never be reached due to the infinite loop)
    close(fd);
    return 0;
}
