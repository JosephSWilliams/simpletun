#include <sys/fcntl.h>
#include <poll.h>
int main(){

fcntl(6,4,2050);
fcntl(7,4,2050);
fcntl(3,4,2050);

struct pollfd fds[4];
fds[0].fd = 6;
fds[0].events = 3;
fds[0].revents = 3;
fds[1].fd = 3;
fds[1].events = 3;
fds[1].revents = 3;
fds[2].fd = 7;
fds[2].events = 4;
fds[2].revents = 4;
fds[3].fd = 3;
fds[3].events = 4;
fds[3].revents = 4;

unsigned char server_buffer[1500] = {0};
unsigned char tunnel_buffer[1500] = {0};
int server_eagain = 0;
int tunnel_eagain = 0;
int out = 0;
int in = 0;

while (1){
  if ((tunnel_eagain)||(poll(&fds[0],1,256-(poll(&fds[1],1,0)*256))>0)){
    if (poll(&fds[3],1,256)>0){
      if (tunnel_eagain<1500){
        in = read(6,&tunnel_buffer[tunnel_eagain],1500-tunnel_eagain);
        if (in<1) break;}
      else in = 0;
      out = write(3,tunnel_buffer,tunnel_eagain+in);
      if (out<0) break;
      if (out<tunnel_eagain+in){
        memmove(tunnel_buffer,&tunnel_buffer[out],tunnel_eagain+in-out);
        tunnel_eagain = tunnel_eagain + in - out;}
      else tunnel_eagain = 0;}}

  if ((server_eagain)||(poll(&fds[1],1,256-(poll(&fds[0],1,0)*256))>0)){
    if (poll(&fds[2],1,256)>0){
      if (server_eagain<1500){
        in = read(3,&server_buffer[server_eagain],1500-server_eagain);
        if (in<1) break;}
      else in = 0;
      out = write(7,server_buffer,server_eagain+in);
      if (out<0) break;
      if (out<server_eagain+in){
        memmove(server_buffer,&server_buffer[out],server_eagain+in-out);
        server_eagain = server_eagain + in - out;}
      else server_eagain = 0;}}}}
