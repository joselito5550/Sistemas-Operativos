#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

 #define TAM 20

 typedef struct array{
   int *matriz_1;
   int *matriz_2;
 } the_param;

void *product(void *aux){
  the_param *estructura;
  estructura = (the_param *)aux;
  int *first_matriz = (*estructura).matriz_1;
  int *second_matriz = (*estructura).matriz_2;
  int i,j;
  int *result = (int *)malloc(sizeof(int));
  *result=0;
  for(i=0;i<3;i++){
    // for(j=0;j<3;j++){
    // printf("Hola i=%d matriz=%d\n",i,aux->matriz_1[i]);
    // }
    *result = (((*estructura).matriz_1[i]) * ((*estructura).matriz_2[i])) + (*result);
  }
  pthread_exit((void *)result);
  free(result);
}

//main program
int main(int argc, char **argv)
{
    the_param aux[3];
    int matriz_1[3][3];
    int matriz_2[3];
    int i,j;
    printf("La matriz es :  \n");
    for (i=0;i<3;i++){
      matriz_2[i] = 2;
      for(j=0;j<3;j++){
        matriz_1[i][j] = i;
        printf("Matriz_1[%d][%d] = %d \n",i,j,matriz_1[i][j]);
      }
    }
    printf("La segunda matriz es una matriz de 3 elementos, todos son 2\n");

    printf("\n");

    pthread_t hebras[3];

    for(i=0;i<3;i++){
      aux[i].matriz_1 = &matriz_1[i][0];
      aux[i].matriz_2 = matriz_2;
      pthread_create(&(hebras[i]),NULL,(void *)product,(void *)&aux[i]);
    }
    int *result;
    int solucion[3];
    for(i=0;i<3;i++){
      pthread_join(hebras[i],(void **)&result);
      //*result = (*result) + (*result);
      solucion[i]=*result;
      printf("\n");
      printf("solucion [%d] = %d\n",i,solucion[i] );
    }
}
