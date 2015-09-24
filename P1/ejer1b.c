#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    pid_t pid;
    int status, childpid,i,flag;
    for(i=0;i<num;i++){
        pid=fork();
        switch(pid)
        {
          case -1: /* error del fork() */
                perror("fork error");
                printf("errno value= %d\n", errno);
                exit(EXIT_FAILURE);

          case 0: /* proceso hijo */
          printf("Proceso (%d); mi padre = %d \n", getpid(), getppid());
                break;
          default: /* padre */
                // printf("PADRE: He tenido un hijo con pid:%d\n",pid);
                wait(&status);
                exit(EXIT_SUCCESS);
            }
    }
    while((flag=wait(&status)) > 0)
    {
      if(WIFEXITED(status))
      {
        printf("El hijo salio, estado=%d\n", WEXITSTATUS(status));
    }else if(WIFSIGNALED(status))
        {
          printf("El hijo murio, (señal %d)\n", WTERMSIG(status));
      }else if(WIFSTOPPED(status))
          {
            printf("El hijo paro, (señal %d)\n", WSTOPSIG(status));
        }else if(WIFCONTINUED(status))
            {
              printf("El hijo continuo\n");
            }
    }

    if(flag == -1 && errno == ECHILD)
    {
      printf("No hay mas hijos que esperar\n");
    }else
      {
        printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
        exit(EXIT_FAILURE);
      }

    exit(EXIT_SUCCESS);
}
