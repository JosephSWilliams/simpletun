#define USAGE "Usage: curvecpclientauth CURVECPCLIENTPUBKEY prog [args]\n"
#include <stdlib.h>
int main(int argc, char **argv){
if ((argc>2)&&(strlen(argv[1])>=64)){
  if (!getenv("CURVECPCLIENTPUBKEY")) exit(64);
  if (strlen(getenv("CURVECPCLIENTPUBKEY"))<64) exit(64);
  if (memcmp(getenv("CURVECPCLIENTPUBKEY"),argv[1],64)) exit(1); /* expects lowercase */
  execvp(argv[2],argv+2);
  exit(255);}
write(2,USAGE,strlen(USAGE));
exit(64);}
