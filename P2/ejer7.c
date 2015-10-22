#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

 #define TAM 20

int global=0;

void *sum_global_var(void *name){
  int i=0;
  while(i<50){
    global++;
    i++;
  }
}

int main(int argc, char **argv)
{
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1,NULL,(void *)sum_global_var,(void *)&global);
    pthread_create(&thread_2,NULL,(void *)sum_global_var,(void *)&global);

    pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);

    printf("La variable global vale :%d\n",global);

}
