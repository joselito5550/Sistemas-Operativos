//
//  ejemplo1.c
//  El pthread_exit devuelve el valor a través de un puntero
//
//  Created by Enrique García Salcines on 10/10/15.
//  Copyright (c) 2015 Universidad de Córdoba. All rights reserved.
//

#include <stdio.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

void *devuelve_entero (int *indice) 
{
    int *valor=(int *)malloc(sizeof(int));
    *valor = *indice*10;
    
    printf("Soy el hilo %d y mi valor es %d\n", *indice, *valor);
    pthread_exit(valor); 
}

int main(void) 
{
    int i,j, N=5;
    int *valor_devuelto;
	int indices[N];
    
    srand(time(NULL));
    
    /* Creación de un conjunto de hebras */ 
    pthread_t thr[N]; //Array de hebras
    
    for(i = 0; i < N; i++) {
        pthread_create( &thr[i], NULL, (void *)devuelve_entero,&i);
		usleep(100000); 
    }
    
    int suma_total = 0;
    for(j = 0; j < N; j++) {
        pthread_join(thr[j], (void **) &valor_devuelto);
        printf("El hilo %d ha devuelto el valor %d\n",i, *valor_devuelto);
    }

    pthread_exit(NULL);
    
}

