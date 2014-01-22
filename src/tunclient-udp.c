#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <strings.h>
#include <stdlib.h>
#define _WITH_DPRINTF
#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{

  if (argc<5)
  {
    dprintf(2,"Usage: tunclient-udp addr port remote_addr remote_port\n");
    exit(64);
  }

  struct sockaddr_in sock;

  int sockfd = -1, optval = 1;
  sockfd = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);

  if (sockfd<0) exit(1);
  if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))<0) exit(2);

  bzero(&sock,sizeof(sock));
  sock.sin_family=AF_INET;
  sock.sin_addr.s_addr=inet_addr(argv[1]);
  sock.sin_port=htons(atoi(argv[2]));

  if (bind(sockfd,(struct sockaddr*)&sock,sizeof(sock))<0) exit(3);

  bzero(&sock,sizeof(sock));
  sock.sin_family=AF_INET;
  sock.sin_addr.s_addr=inet_addr(argv[3]);
  sock.sin_port=htons(atoi(argv[4]));

  if (connect(sockfd,(struct sockaddr*)&sock,sizeof(sock))<0) exit(4);

  if (fcntl(sockfd,F_GETFL,0)<0) exit(5);
  close(6);
  if (fcntl(sockfd,F_DUPFD,6)<0) exit(6);
  if (fcntl(6,F_GETFL,0)<0) exit(7);
  close(7);
  if (fcntl(6,F_DUPFD,7)<0) exit(8);

  struct pollfd fds[2];
  fds[0].fd = 6;
  fds[0].events = POLLIN;
  fds[1].fd = 3;
  fds[1].events = POLLIN;

  int n;
  unsigned char buffer[1500];

  while (1)
  {

    poll(fds,2,-1);

    if (fds[1].revents)
    {
      n = read(3,buffer,1500);
      if (n<0) exit(9);
      write(7,buffer,n);
    }

    if (fds[0].revents)
    {
      n = read(6,buffer,1500);
      if (n<0) exit(10);
      if (write(3,buffer,n)<0) exit(11);
    }

  }

}
