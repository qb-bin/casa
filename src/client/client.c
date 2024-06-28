#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 256
#define  PORT       2024
#define ADDRESS     "192.168.1.105"

int main() {
     puts("[CASA STARTED]");

    int socket1;
    char *message = "connetion established\n";
    char buffer[BUFFER_SIZE];

    struct hostent *server;
    struct sockaddr_in client_addr, server_addr;
    socklen_t server_addr_len;

    if((socket1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    } 

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("addr");
        exit(1);
    }

    if((connect(socket1, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
        perror("connect");
        exit(1);
    }

    if((read(socket1, buffer, BUFFER_SIZE - 1)) < 0) {
        perror("read");
        exit(1);
    } 
    printf("%s", buffer);
 
    if(send(socket1, message, strlen(message), 0) < 0) {
        perror("send");
        exit(1);
    } 
     
    close(socket1);
    return 0;
}