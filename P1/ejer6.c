#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
    int global = 0;
    pid_t pid;
    int status, childpid,i;
        pid=fork();
        switch(pid)
        {
          case -1: /* error del fork() */
                perror("fork error");
                printf("errno value= %d\n", errno);
                exit(EXIT_FAILURE);

          case 0: /* proceso hijo */
          printf("Proceso hijo aumentando la variable global \n");
          global++;
                exit(EXIT_SUCCESS);
                break;
          default: /* padre */
                 printf("Padre: Mostrando la variable global %d\n",global);
                 childpid=wait(&status);
            }
    exit(EXIT_SUCCESS);
}
