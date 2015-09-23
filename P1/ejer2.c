#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){
    pid_t pid;
    int status, childpid;

    pid=fork();
    switch(pid){
        case -1:
            perror("fork error");
            printf("errno value= %d\n", errno);
				exit(EXIT_FAILURE); //Necesaria la librería <stdlib.h>
            //return (-1);

        case 0: /* proceso hijo */
            printf("ProcesoHIJO %d; mi padre = %d \n", getpid(), getppid());


        default: /* padre */
            sleep(20);
            exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
