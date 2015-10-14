#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define TAM 100

void *sumvector(void *vector)
{
    int *random1;
    int *random2;
    int i = *((int *)parametro);
    random1 = (int *)malloc(sizeof(int));
    random2 = (int *)malloc(sizeof(int));
    *random1 = rand()%10;
    *random2 = rand()%10;
    printf("Soy una hebra, devuelvo %d + %d = %d\n",*random1,*random2,*random1+*random2);
    *random1 = *random1 + *random2;
    pthread_exit((void *)random1);
}

int main(int argc, char **argv)
{
    //Check
     if(argc!=2){
         printf("./ejer1 N_hebras\n");
         exit(-1);
     }
     int i;
     void *num;
     int sum_threads = 0;
     int num_thread = atoi(argv[1]);
     int vector[10];
     for (i=0;i<10;i++){
         vector[i]=i;
     }
	//Declaración de dos hebras, hilos o procesos ligeros. NO CREACION
    pthread_t hebras[10];

    //create the threads
    for(i=0;i<num_thread;i++){
        pthread_create(&(hebras[i]),NULL,sumvector,(void *)vector);
    }

    for(i=0;i<num_thread;i++){
        pthread_join(hebras[i],(void **)&num);
        sum_threads=sum_threads+*(int *)num;
        printf("Me han devuelto %d con id: %d\n",*(int *)num, i);
        //sum_threads+=*num;
    }
    printf("Soy el main la suma de todos es: %d\n",sum_threads);
}
