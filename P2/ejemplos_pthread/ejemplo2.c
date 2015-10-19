//
//  ejemplo2.c
//  El pthread_exit devuelve una estructura
//
//  Created by Enrique García Salcines on 10/10/15.
//  Copyright (c) 2015 Universidad de Córdoba. All rights reserved.
//

#include <stdio.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

typedef struct param {
    int a;
    int b;
} the_params;

void *devuelve_estructura (int *nhebra) 
{
    the_params *parametros;
    parametros=(the_params *)malloc(sizeof(the_params));
    parametros->a = 10*(*nhebra);
    parametros->b = 20*(*nhebra);
    
    printf("Soy la hebra nº: %d. Mis numeros son %d y %d\n",*nhebra,parametros->a,parametros->b);
    
    pthread_exit(parametros); 
}

int main(void) 
{
    int i,j, N=5;
    the_params *aux;
	int indices[N];
    
    /* Creación de un conjunto de hebras */ 
    pthread_t thr[N]; //Array de hebras
    
    for(i = 0; i < N; i++) {
        pthread_create( &thr[i], NULL, (void *)devuelve_estructura,&i);
		usleep(100000); 
    }
    
    int suma_total = 0;
    for(i = 0; i < N; i++) {
        pthread_join(thr[i], (void **) &aux);
		printf("Resultado hebra nº: %d --> a=%d y b=%d\n",i,aux->a, aux->b);
    }

    return 0;
    
}

