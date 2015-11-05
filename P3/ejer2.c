#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#define NUMTHRDS 3
#define VECLEN 3

//Semaforo
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


void * funct_threads(void *argv){
  char *caracter = (char *)argv;
  int i = 0;
  int s = pthread_mutex_lock(&mtx);
  if(s!=0)
    printf("Mutex_lock error...\n");
  //Seccion critica
  for(i=0;i<5;i++){
  printf("%c", *caracter);
  fflush(stdout);
  sleep(1);
  }
  //Fin de la sección critica
  s = pthread_mutex_unlock(&mtx); /*Unlock the mutex*/
  if (s != 0)
      printf("mutex_unlock error...\n");
}

int main (int argc, char *argv[])
{
    pthread_t threads[NUMTHRDS];
    int i;
    char a = 'a';
    char b = 'b';
    char c = 'c';

    pthread_create(&(threads[0]),NULL,funct_threads,(void *)&a);
    pthread_create(&(threads[1]),NULL,funct_threads,(void *)&b);
    pthread_create(&(threads[2]),NULL,funct_threads,(void *)&c);

    //inicio de la seccion critica
    int s = pthread_mutex_lock(&mtx);
    printf("?????");
    //fin de la seccion critica
    s = pthread_mutex_unlock(&mtx);

    //Esperamos los hilos
    for(i=0;i<3;i++){
      pthread_join(threads[i],NULL);
    }
}
