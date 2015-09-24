#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){
    pid_t pid;
    int status, childpid;

    //primer hijo
    pid=fork();
    if(pid==0){
          if(execlp(argv[1],"",NULL)==-1){
                perror("Falla la ejecuion exec ");
                exit(EXIT_FAILURE);
          }
          exit(EXIT_SUCCESS);
   }

    //segundo hijo
    pid=fork();
    if(pid==0){
          if(execvp(argv[2],&argv[2])==-1){
                perror("Falla la ejecuion exec");
                exit(EXIT_FAILURE);
          }
          exit(EXIT_SUCCESS);
   }
   while(wait(&status)!=-1){

   }

    exit(EXIT_SUCCESS);
}
