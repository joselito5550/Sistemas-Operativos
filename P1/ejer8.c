#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void controlador(){
  printf("He recibido una señal de mi padre\n");
}

int main(){
    pid_t pid;
    int status, childpid, i;

    pid=fork();
    switch(pid){
        case -1:
            perror("fork error");
            printf("errno value= %d\n", errno);
				exit(EXIT_FAILURE); //Necesaria la librería <stdlib.h>
            //return (-1);

        case 0: /* proceso hijo */
            signal(SIGUSR1,controlador);
            while(1){
              pause();
            }

        default: /* padre */
            sleep(2);
            for(i=0;i<4;i++){
              kill(pid,SIGUSR1);
              sleep(1);
            }
            kill(pid,SIGINT);
    }
    exit(EXIT_SUCCESS);
}
