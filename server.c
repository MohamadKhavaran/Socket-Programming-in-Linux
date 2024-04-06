#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include  <errno.h>
#include<stdlib.h>
#include<string.h>
#define MAX 4000
int main(int argc, char *argv[])
{

  int status;
  struct sockaddr *theiraddr;
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof hints); //All Member of address info got 0
  hints.ai_family = AF_INET; 
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, argv[1], &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 1;
  }

 int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //Create Socket
 if(bind(sockfd, res->ai_addr, res->ai_addrlen) < 0)//Error IN Connection 
 {
printf("Not Bind !");
if(errno==EADDRINUSE) 
{
    printf("Port Is Used");
}
exit(1);
 }
 listen(sockfd,1);  //up to 1 connection requets can be queued (backlog = 3)
printf("Listening ...\n");
   int new_fd = accept(sockfd,theiraddr,(socklen_t *) sizeof theiraddr);
   if(new_fd < 0)
   {
    printf("Connection Field ");
    exit(1);
   }
   printf("A new client connected to server ");
   char input[MAX];
   char output[MAX];
 while(1){
   printf("127.0.0.1 $");
   fgets(input,MAX,stdin);
   send(new_fd,input,strlen(input),0); //Send To Client
   recv(new_fd, output, MAX, 0);
   printf("\n%s",output) ;
   memset(output, 0, MAX);
   memset(input, 0, MAX);
   
   
 }
  return 0;
}
