#define USAGE "Usage: recvpasswd passwd prog [args]\n"
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
 int i, n, ret=0;
 unsigned char passwd0[256]={0};
 unsigned char passwd1[256]={0};
 if ((argc>2)&&((n=strlen(argv[1])&255))) {
  memcpy(passwd0,argv[1],n);
  if (read(0,passwd1,n)<n) exit(32);
  for (i=0;i<256;++i) ret |= (passwd0[i]!=passwd1[i]) ? 1 : 0;
  if (!ret) execvp(argv[2],argv+2);
 }
 write(2,USAGE,strlen(USAGE));
 exit(64);
}
