#define USAGE "Usage: curvecpclientauth CURVECPCLIENTPUBKEY prog [args]\n"
int main(int argc, char **argv){
if ((argc>2)&&(strlen(argv[1])>=64)){
  if (memcmp(getenv("CURVECPCLIENTPUBKEY"),argv[1],64)) exit(0); /* expects lowercase */
  if (execvp(argv[2],argv+2)<0) exit(255);}
write(2,USAGE,strlen(USAGE));
exit(64);}
