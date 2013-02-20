#include <poll.h>
main(){

struct pollfd fds[4];
fds[0].fd = 6;
fds[0].events = 3;
fds[0].revents = 3;
fds[1].fd = 3;
fds[1].events = 3;
fds[1].revents = 3;
fds[2].fd = 3;
fds[2].events = 4;
fds[2].revents = 4;

unsigned char p[1502] = {0};
int i=0, n=0, len=0;

while (1){

  if ((poll(&fds[0],1,256)>0)&&(poll(&fds[2],1,256)>0)){
    len=read(6,p,2);
    if (2>len) exit(0);
    len=p[0]*256+p[1];
    if (1500<len) exit(0);
    i=0; n=0;
    while(n<len){
      i=read(6,&p[n],len-n);
      if (i<1) exit(0);
      n+=i;}
    write(3,p,len);}

  if (poll(&fds[1],1,256)>0){
    len=read(3,&p[2],1500);
    if (0>len) exit(0);
    p[0]=len/256; p[1]=len%256;
    write(7,p,2+len);}}}
