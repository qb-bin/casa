#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main() {
  
    struct addrinfo hints, *res, *p;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if(getaddrinfo(NULL, "9090", &hints, &res)) {
      perror("getaddrinfo");
    } 
    p = res;

    printf("%i ", AF_INET);
    printf("%i\n", AF_INET6);
    while(p != NULL) {
      fprintf(stdout, "%i ", p->ai_addr->sa_family);
      p = p->ai_next;
    }
    printf("\n");

    freeaddrinfo(res);
    return 0;
}
