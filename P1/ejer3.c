#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){
    pid_t pid;
    int status, childpid,flag;
    int suma=0;
    //Crear el primer hijo
    pid=fork();
    if(pid==0){
        //El primer hijo no tiene que tener mas hijos
        printf("Soy el primer hijo (pid=%d) y mi suma es %d\n", getpid(),getpid()%10);
        exit((getpid()%10));
    }

    //Crear el segundo hijo
    pid=fork();
    if(pid==0){
        //El segundo hijo tiene que tener dos hijos
        //Primer nieto
        pid=fork();
            if(pid==0){
                printf("Soy el primer nieto (pid = %d) y mi suma es: %d\n",getpid(),getpid()%10);
                exit(getpid()%10);
            }
        //segundo nieto (tiene que tener un hijo)
        pid=fork();
        if(pid == 0){
            //tiene el bisnieto
            pid=fork();
            if(pid==0){
                printf("Soy el bisnieto (pid = %d) y mi suma es: %d\n",getpid(),getpid()%10);
                exit(getpid()%10);
            }
            wait(&status);
            printf("Soy el segundo nieto (pid = %d) y mi suma es: %d\n",getpid(),WEXITSTATUS(status)+(getpid()%10));
            exit(WEXITSTATUS(status)+(getpid()%10));
        }
        while((flag=wait(&status))>0){
            suma+=WEXITSTATUS(status);
        }
        printf("Soy el segundo hijo (pid = %d) y mi suma es: %d \n",getpid(),suma+(getpid()%10) );
        exit(suma+(getpid()%10));
    }


    //Esperar a sus hijos
    while((flag=wait(&status))>0){
        //Hacer la suma
        suma+=WEXITSTATUS(status);
    }
    printf("Soy el padre (pid = %d) y mi suma es: %d\n",getpid(),suma+(getpid()%10) );
    exit(EXIT_SUCCESS);
}
