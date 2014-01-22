#include <stdlib.h> 
#include <poll.h>
#include <unistd.h>

int main(){

struct pollfd fds[2];
fds[0].fd=0; fds[0].events=POLLIN|POLLPRI;
fds[1].fd=3; fds[1].events=POLLIN|POLLPRI;

int i=0, n=0, len=0;
unsigned char p[1502]={0};

while (1){

  poll(fds,2,-1);

  if (fds[0].revents){
    len=read(0,p,2);
    if (2>len) exit(1);
    len=p[0]*256+p[1];
    if (len){
      if (1500<len) exit(2);
      i=0; n=0;
      while(n<len){
        i=read(0,&p[n],len-n);
        if (i<1) exit(3);
        n+=i;}
      if (write(3,p,len)<0) exit(4);}}

  if (fds[1].revents){
    len=read(3,&p[2],1500);
    if (0>len) exit(5);
    p[0]=len/256; p[1]=len%256;
    if (write(1,p,2+len)<0) exit(6);}}}
