#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define  PORT       2024
#define ADDRESS     "192.168.1.105"
#define BUFFER_SIZE 1024

int main() {

    int socket1;
    char *message = "client connected\n";

    char input[128];
    char file_name[128];
    char *buffer;
    buffer = malloc(sizeof(char) * BUFFER_SIZE);

    DIR *dir = NULL;
    struct dirent *d;

    int i = 0, lfd = 0;

    printf("> ");
    fgets(input, sizeof(input), stdin);

    while(input[i] != '\n') {
        i++;

    }
    input[i] = '\0';

    dir = opendir(input);
    if(dir == NULL) {
        perror("directory opening");
        exit(EXIT_FAILURE);
    }

    while((d = readdir(dir)) != NULL){
        if(d->d_name[0] != '.') {
            if (d->d_type == 4) {
                printf("%s/\n", d->d_name);
            }
            else {
                printf("%s\n", d->d_name);
            }
        }
    }    

    fprintf(stdout, "select a file : ");
    fgets(file_name, sizeof(file_name), stdin);
    i = 0;
    
    while(file_name[i] != '\n') { 
        i++;
    }
    file_name[i] = '\0';

    printf("path : %s/", input);
    printf("%s\n", file_name);

    if((chdir(input))) {
        perror("error while changing dir");
        exit(EXIT_FAILURE);
    }

    if(!(lfd = open(file_name, O_RDONLY))) {
        perror("file opening");
        exit(EXIT_FAILURE);
    }

    read(lfd, buffer, BUFFER_SIZE);
    printf("%s \n", buffer);

    free(buffer);
    close(lfd);
    closedir(dir);

    puts("[CASA STARTED]");

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
 
    if(send(socket1, buffer, BUFFER_SIZE, 0) < 0) {
        perror("send");
        exit(1);
    } 
     
    close(socket1);
    return 0;
}
