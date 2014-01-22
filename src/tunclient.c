#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#ifdef __OpenBSD__
  #include <sys/socket.h>
#endif
#include <stdio.h>
int main(){
  struct pollfd fds[2];
  fds[0].fd=6; fds[0].events=POLLIN|POLLPRI;
  fds[1].fd=3; fds[1].events=POLLIN|POLLPRI;

  int i=0, n=0, len=0;
  unsigned char p[1502]={0};

  while (1){
    poll(fds,2,-1);
    if (fds[0].revents){
      len=read(6, p, 2);
      if (2>len) exit(1);
      len=p[0]*256+p[1];
      if (len){
        if (1500<len) exit(2);
        #ifdef __OpenBSD__
          i=0; n=4;
          len += 4;
        #else
          i=0; n=0;
        #endif
        while(n<len){
          i=read(6,&p[n],len-n);
          n+=i;
          if (i<1) exit(3);
        }
        #ifdef __OpenBSD__
          int pihdr = 0;
          int ipver = (p[4] >> 4) & 0xf;
          //dprintf(2, "got remote packet with ip version %i\n", ipver);
          if (ipver == 4) pihdr = htonl(AF_INET);
          else if (ipver == 6) pihdr = htonl(AF_INET6);
          *(int*)(p) = pihdr;
        #endif
        if (write(3,p,len)<0) {
          dprintf(2, "could not write %i bytes to TUN\n", len);
          perror("reason");
          exit(4);
        }
      }
    }

    if (fds[1].revents){
      #ifdef __OpenBSD__
        len=read(3,&p[0],1500);
        if (0>len) exit(5);
        len -= 4;
        p[2]=len/256; p[3]=len%256;
        if (write(7,p+2,2+len)<0) {
          dprintf(2, "could not write %i bytes to socket\n", len);
          perror("reason");
          exit(6);
        }
      #else
        len=read(3,&p[2],1500);
        if (0>len) exit(5);
        p[0]=len/256; p[1]=len%256;
        if (write(7,p,2+len)<0) exit(6);
      #endif
      }
    }
}
