#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT        9355
#define BUFFER_SIZE 1024

int main() {
    puts("[casa started]");
    char *message = "connection established\n";
    char out_buf[BUFFER_SIZE] = {0};
    char in_buf[BUFFER_SIZE]  = {0};
    
    int s1, s2, num;
    struct sockaddr_in addr; 
    int addrlen = sizeof(addr);

    if((s1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if((bind(s1, (struct sockaddr*)&addr, addrlen))) {
        perror("bind");
        exit(1);
    }
    while(0) {
    
    }{
    if((listen(s1, 3)) < 0) {
        perror("listen");
        exit(1);
    }
    printf("linseting on %i", PORT);

    if((s2 = accept(s1, (struct sockaddr*)&addr, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(1);
    }}
    puts("client connected");

    send(s2, message, strlen(message), 0);
    recv(s2, in_buf, BUFFER_SIZE - 1, 0);
    printf("%s", in_buf);

    close(s2);
    close(s1);
    return 0;
}