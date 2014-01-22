#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#ifdef linux
  #include <linux/if_ether.h>
  #include <linux/if_tun.h>
#else
  #include <sys/types.h>
  #include <net/if_tun.h>
  #ifndef HAVE_NETINET_IN_H
    #include <netinet/in.h>
  #endif
  #include <sys/socket.h>
#endif

#include <net/if.h>
#define USAGE "Usage: tun ifr_name prog [args]\n"
int main(int argc, char **argv){
if ((argc>2)&&(strlen(argv[1])>0)&&(strlen(argv[1])<17)){
  #ifdef linux
    if (open("/dev/net/tun",2)!=3) exit(255);
    struct ifreq ifr;
    memset(&ifr,0,sizeof(ifr));
    strcpy(ifr.ifr_name,argv[1]);
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    if (ioctl(3,TUNSETIFF,(void *)&ifr)<0) exit(255);
  #else
    char ifr_name[5+16]={0};
    memmove(&ifr_name,"/dev/",5);
    memmove(&ifr_name[5],argv[1],strlen(argv[1]));
    if (open(ifr_name,2)!=3) exit(255);
    int ifr_flag = IFF_POINTOPOINT | IFF_MULTICAST;
    if (ioctl(3,TUNSIFMODE,&ifr_flag)<0) exit(255);
    #ifndef __OpenBSD__
      ifr_flag=0; if (ioctl(3,TUNSLMODE,&ifr_flag)<0) exit(255);
      ifr_flag=0; if (ioctl(3,TUNSIFHEAD,&ifr_flag)<0) exit(255);
    #endif
  #endif
  execvp(argv[2],argv+2);}
write(2,USAGE,strlen(USAGE));
exit(64);}
