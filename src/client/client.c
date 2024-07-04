#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024 
#define  PORT       2024

int main(int args, char *argc[]) {
    char *DOMAIN = argc[1];
    int sfd0;
    struct addrinfo hints, *res;
    struct sockaddr_in serveraddr;
    char buffer[BUFFER_SIZE];
    char ipstr[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((getaddrinfo(DOMAIN, NULL, &hints, &res)) < 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }
    
    serveraddr.sin_port        = htons(PORT);
    serveraddr.sin_family      = AF_INET;
    serveraddr.sin_addr        = ((struct sockaddr_in *)res->ai_addr)->sin_addr;
    
    inet_ntop(AF_INET, &serveraddr.sin_addr.s_addr, ipstr, sizeof(ipstr));
    printf("%s\n", ipstr);

    if ((sfd0 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (connect(sfd0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    recv(sfd0, buffer, BUFFER_SIZE, 0);
    puts("recived");
    for(int i = 0; i < 10; i++) {
        printf("%c", buffer[i]);
    }
    
    freeaddrinfo(res);
    close(sfd0);
    return 0;
}
