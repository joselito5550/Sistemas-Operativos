#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#define MAX_ITEMS 20

//Semaforo
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int contador = 0; //Contador de elementos
int buffer[5];    //buffer
int N = 5;  //Numero de elementos
int consumidos[MAX_ITEMS];

void *productor(void *argv){
      int num_items = 0;
      int i;
      int pos_buffer = 0;
      srand(time(NULL));
      while( num_items < MAX_ITEMS){
            usleep(rand()%100000);
            //block Mutex_lock
            pthread_mutex_lock(&mtx);
            if (contador != N){
                  buffer[pos_buffer] = rand()%10;
                  printf("P: METI EN BUFFER %d \n ",buffer[pos_buffer]);
                  pos_buffer= (++pos_buffer) % N;
                  contador++;
                  fflush(stdout);
                  num_items++;
            }
      //      for(i = 0;i<contador;i++){
      //            printf("[%d]",buffer[i]);
      //            fflush(stdout);
      //      }
      pthread_mutex_unlock(&mtx);
      }
}

void *consumidor(void *argv){
      int num_items = 0;
      int i=0;
      int pos_buffer = 0;
      srand(time(NULL));
      while (num_items < MAX_ITEMS) {
            usleep(rand()%100000);
            pthread_mutex_lock(&mtx);
            if(contador !=0){
                  consumidos[i] = buffer[pos_buffer];
                  printf("C: LEI DEL BUFFER %d \n ",buffer[pos_buffer]);
                  pos_buffer = (++pos_buffer) % N;
                  contador--;
                  num_items++;

            }
            pthread_mutex_unlock(&mtx);
      }
}

int main(int argc, char *argv[]){
      pthread_t product;
      pthread_t consum;

      pthread_create(&product,NULL,productor,NULL);
      sleep(1);
      pthread_create(&consum,NULL,consumidor,NULL);

      pthread_join(product,NULL);
      pthread_join(consum,NULL);

      pthread_mutex_destroy(&mtx);
}
