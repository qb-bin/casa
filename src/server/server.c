#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT       2024
#define BUFFERSIZE 256

int main() {
    int server = -1, client = -1;
    char buffer[BUFFERSIZE];

    struct sockaddr_in serveraddr;

    if(!(server = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    printf("socket fd : %i\n", server);
    
    
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_port          = htons(PORT);
    serveraddr.sin_family        = AF_INET;
    serveraddr.sin_addr.s_addr   = INADDR_ANY; 

    if((bind(server, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }  

    if(listen(server, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    puts("[waiting for connection]");

    if((client = accept(server, NULL, NULL)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
