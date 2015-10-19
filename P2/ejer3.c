#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define TAM 10

typedef struct param {
    int indice;
    int *mivector;
    int num_elementos;
} the_param;

void *sumvector(void *structura){
    int i;
    int *suma = (int *)malloc(sizeof(int));
    the_param *aux;
    aux = (the_param *)structura;
    int indice = (*aux).indice;
    int num_elementos = (*aux).num_elementos;
    num_elementos = num_elementos+indice;
    for(i=indice;i<num_elementos;i++){
        *suma= *suma+(*aux).mivector[i];
        printf("Sumando vector[%d]=%d ---> suma total = %d\n",i,aux->mivector[i],*suma );
    }
    pthread_exit((void *)suma);
}

int main(int argc, char **argv)
{
    if(argc != 2){
        printf("./ejer3 Numero_hebras\n");
        exit(0);
    }

    int NH = atoi(argv[1]);
    int mivector[TAM];
    int i,num;
    pthread_t hebras[TAM];
    the_param aux;
    the_param array[TAM];

    for(i=0;i<TAM;i++){
        mivector[i] = 1;
        printf("vector[%d]=%d\n",i,mivector[i]);
    }
    aux.mivector = mivector;
    num = TAM/NH;
    aux.num_elementos = num;
    for(i=0;i<NH;i++){
        aux.indice = i*num;
        if (i==NH-1){
            aux.num_elementos += (TAM%NH);
        }
        array[i] = aux;
        pthread_create(&(hebras[i]),NULL,(void *)sumvector,(void *)&array[i]);

    }

    int *suma;
    int suma_total = 0 ;
    for(i=0;i<NH;i++){
        pthread_join(hebras[i],(void **)&suma);
        printf("Suma recibida del hilo: %d ----> %d \n",i,*suma );
        suma_total+=(*suma);
    }
    printf("Suma total = %d\n",suma_total );

}
