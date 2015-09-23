#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    pid_t pid;
    int status, childpid,i;
    for(i=0;i<num;i++){
        pid=fork();
        switch(pid)
        {
          case -1: /* error del fork() */
                perror("fork error");
                printf("errno value= %d\n", errno);
                exit(EXIT_FAILURE);

          case 0: /* proceso hijo */
          printf("Proceso hijo %d; mi padre = %d \n", getpid(), getppid());
                exit(EXIT_SUCCESS);
                break;
          default: /* padre */
                 printf("PADRE: He tenido un hijo con pid:%d\n",pid);
                 childpid=wait(&status);
            }
    }
    exit(EXIT_SUCCESS);
}
