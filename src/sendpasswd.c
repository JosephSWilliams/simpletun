#define USAGE "Usage: sendpasswd passwd prog [args]\n"
int main (int argc, char **argv) {
if (argc>2){
  write(7,argv[1],strlen(argv[1]));
  execvp(argv[2],argv+2);}
write(2,USAGE,strlen(USAGE));
exit(64);}
