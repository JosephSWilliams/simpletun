#define USAGE "Usage: recvpasswd passwd prog [args]\n"
int main (int argc, char **argv) {
if (argc>2){
  char *passwd = (char *)malloc(sizeof(char)*strlen(argv[1]));
  if (!passwd) exit(64);
  read(0,passwd,strlen(argv[1]));
  if (memcmp(passwd,argv[1],strlen(argv[1]))) exit(1);
  execvp(argv[2],argv+2);}
write(2,USAGE,strlen(USAGE));
exit(64);}
