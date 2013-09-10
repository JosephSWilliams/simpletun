#define USAGE "Usage: dh <pubkey> <seckey>\n"
#include <nacl/crypto_box.h>
#include <stdlib.h>
#include <string.h>
#include <base16.h>

main(int argc, char *argv[]) {
 unsigned char s[32], p[32], k[32], ret[64];
 if ((argc<3)
 || (strlen(argv[1])!=64)
 || (strlen(argv[2])!=64)
 || (base16_decode(p,argv[1],64)!=32)
 || (base16_decode(s,argv[2],64)!=32)
 || (crypto_box_beforenm(k,p,s)<0))
 {
  write(1,USAGE,strlen(USAGE));
  exit(64);
 }
 base16_encode(ret,k,32);
 write(1,ret,64);
 write(1,"\n",1);
}
