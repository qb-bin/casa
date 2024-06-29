#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
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
    return 0;
}