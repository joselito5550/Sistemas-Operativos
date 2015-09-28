#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){
    pid_t pid;
    int status, childpid,i;
    FILE *f = fopen(argv[1],"w");

    pid=fork();
    if(pid==0){
         for(i=0;i<10;i++){
               fprintf(f," %s", "++++++++++++\n");
               sleep(1);
         }
         //son close file
         fclose(f);
         exit(EXIT_SUCCESS);
   }
   else {
         for(i=0;i<10;i++){
               fprintf(f," %s", "---------------------\n");
               sleep(1);
         }
   }
   wait(&status);
   //dad close file
   fclose(f);
    exit(EXIT_SUCCESS);
}
