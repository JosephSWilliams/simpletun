#define USAGE "Usage: tun iface prog [args]\n"
#include <sys/ioctl.h>
main(int argc, char **argv){
if ((argc>2)&&(strlen(argv[1])>0)&&(strlen(argv[1])<17)){
  unsigned char iface[18]={0};
  #ifdef linux
    memmove(&iface[1],argv[1],strlen(argv[1]));
    ++iface[17];
    if (open("/dev/net/tun",2)!=3) exit(255);
    if (ioctl(3,1074025674,&iface[1])<0) exit(255);
  #else
    memmove(&iface,"/dev/",5);
    memmove(&iface[5],argv[1],strlen(argv[1])%16);
    if (open(iface,2)!=3) exit(255);
  #endif
  execvp(argv[2],argv+2);}
write(2,USAGE,strlen(USAGE));
exit(64);}
