#include <sys/time.h>
#include <poll.h>
main(){

struct timezone *UTC = (struct timezone *)0; /* keepalive hack: upstream should consider */
struct timeval ping, pong, last, seen; /* a flag for longterm connections with */
gettimeofday(&ping,UTC); last=ping; /* considerable periods of silence. */

last.tv_sec-=112; /* don't wait 2 minutes if connection flaps */
write(1,"\x00\x00",2); /* send keepalive immediately */

struct pollfd fds[2]; /* POLLIN | POLLPRI */
fds[0].fd=0; fds[0].events=3; fds[0].revents=3;
fds[1].fd=3; fds[1].events=3; fds[1].revents=3;

unsigned char p[1502] = {0};
int i=0, n=0, len=0;

while (1){

  gettimeofday(&seen,UTC); /* die: lost client */
  if (seen.tv_sec-last.tv_sec>128) exit(0);

  pong=seen;
  if (pong.tv_sec-ping.tv_sec>16){ ping=pong; write(1,"\x00\x00",2); }

  if (poll(&fds[0],1,256)>0){
    len=read(0,p,2);
    if (2>len) exit(1);
    len=p[0]*256+p[1];
    if (len){ /* ignore keepalive packets */
      if (1500<len) exit(2);
      i=0; n=0;
      while(n<len){
        i=read(0,&p[n],len-n);
        if (i<1) exit(3);
        n+=i;}
      if (write(3,p,len)<0) exit(4);}
    last=seen;}

  if (poll(&fds[1],1,256)>0){
    len=read(3,&p[2],1500);
    if (0>len) exit(5);
    p[0]=len/256; p[1]=len%256;
    if (write(1,p,2+len)<0) exit(6);
    ping=pong;}}}
