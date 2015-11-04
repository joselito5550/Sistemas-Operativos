#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMTHRDS 5
#define VECLEN 3

int camisetas[5];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


void * Cliente(){
  int s = pthread_mutex_lock(&mtx);
  if(s!=0)
    printf("Mutex_lock error...\n");
  //Seccion critica
  printf("Soy la hebra ... voy a acceder a la seccion critica\n");
  int i = rand()%5;
  camisetas[i] = camisetas[i] - 1;
  printf("[CLIENTE]  Modelo=%d, quedan %d unidades\n",i,camisetas[i]);
  //Desbloqueamos el semaforo
  printf("Thread %ld pongo el semaforo en verde\n", (unsigned long) pthread_self()); s = pthread_mutex_unlock(&mtx); /*Unlock the mutex*/
  if (s != 0)
      printf("mutex_unlock error...\n");
}


void * Proveedor(){
  int s = pthread_mutex_lock(&mtx);
  if(s!=0)
    printf("Mutex_lock error...\n");
  //Seccion critica
  printf("Soy la hebra ... (proveedor)voy a acceder a la seccion critica\n");
  int i = rand()%5;
  camisetas[i] = camisetas[i] + 1;
  printf("[PROVEEDOR] Modelo=%d, ahora hay %d unidades\n",i,camisetas[i]);
  //Desbloqueamos el semaforo
  printf("Thread %ld pongo el semaforo en verde\n", (unsigned long) pthread_self()); s = pthread_mutex_unlock(&mtx); /*Unlock the mutex*/
  if (s != 0)
      printf("mutex_unlock error...\n");
}


int main (int argc, char *argv[])
{
    if(argc!=2){
        printf("./ejer1 Num_Clientes");
        exit -1;
    }
    srand(time(NULL));
    printf("Tomamos como ejejmplo solo a 5 proveedores\n");
    int num_proveedores = 5;
    int num_clientes = atoi(argv[1]);
    pthread_t hilos_Clientes[NUMTHRDS];
    pthread_t hilos_Proveedores[NUMTHRDS];
    int i;

    //Rellenar el array de las camisetas
    for(i=0;i<num_proveedores;i++){
        camisetas[i] = 5;
    }

    for(i=0;i<num_clientes;i++){
      pthread_create(&(hilos_Clientes[i]),NULL,Cliente,NULL);
      pthread_create(&(hilos_Proveedores[i]),NULL,Proveedor,NULL);
    }
    for(i=0;i<num_clientes;i++){
      pthread_join(hilos_Clientes[i],NULL);
      pthread_join(hilos_Proveedores[i],NULL);
    }
    for(i=0;i<5;i++){
      printf("Camiseta[%d] = %d\n",i,camisetas[i]);
    }
}
