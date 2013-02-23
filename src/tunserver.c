#include <sys/time.h>
#include <poll.h>
main(){

struct timeval now, then;
gettimeofday(&then,(struct timezone *)0);

struct pollfd fds[2];
fds[0].fd = 0;
fds[0].events = 3;
fds[0].revents = 3;
fds[1].fd = 3;
fds[1].events = 3;
fds[1].revents = 3;

unsigned char p[1502] = {0};
int i=0, n=0, len=0;

while (1){

  /* keepalive hack: upstream should consider */
  /* a flag for longterm connections with     */
  /* considerable periods of silence.         */

  gettimeofday(&now,(struct timezone *)0);

  if (now.tv_sec-then.tv_sec>16){
    gettimeofday(&then,(struct timezone *)0);
    write(1,"\x00\x00",2);}

  if (poll(&fds[0],1,256)>0){
    len=read(0,p,2);
    if (2>len) exit(1);
    len=p[0]*256+p[1];
    if (!len) continue;
    if (1500<len) exit(2);
    i=0; n=0;
    while(n<len){
      i=read(0,&p[n],len-n);
      if (i<1) exit(3);
      n+=i;}
    write(3,p,len);}

  if (poll(&fds[1],1,256)>0){
    len=read(3,&p[2],1500);
    if (0>len) exit(4);
    p[0]=len/256; p[1]=len%256;
    write(1,p,2+len);}}}
