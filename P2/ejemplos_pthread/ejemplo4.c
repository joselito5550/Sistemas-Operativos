//
//  ejemplo4.c
//  El pthread_exit() devuelve null, pero el hilo modifica 
//  la variable que se le pasa.
//  Created by Enrique García Salcines on 10/10/15.
//  Copyright (c) 2015 Universidad de Córdoba. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>

#define MAX 5000
#define MITAD (MAX/2)

typedef struct {
    int *ar;
    long n;
} subarray_t;

// Thread que incrementa n componentes de un array
void * incrementer (subarray_t *arg) {
    long i;
    for (i=0; i < arg->n; i++) {
        arg->ar[i]++;
    } 
    pthread_exit(NULL);
}

// programa principal que reparte entre dos threads el trabajo
// de incrementar los componentes de un array
int main() {
    int ar [MAX]; 
    long suma=0,i;
    
    pthread_t th1,th2;
    subarray_t sb1,sb2;
    
    // inicializa los elementos a 1
    for (i=0; i<MAX; i++)
        ar[i] = 0;        

    // crea los theads
    sb1.ar = &ar[0]; sb1.n = MITAD; // primera mitad del array
    pthread_create(&th1, NULL, (void *)incrementer, &sb1);
    sb2.ar = &ar[MITAD]; sb2.n = MITAD; // segunda mitad del array
    
    pthread_create(&th2, NULL, (void *)incrementer, &sb2);
    // sincronizacion de espera a la finalizacion
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf ("Ambos threads han finalizado \n");
    // muestra resultados 
    for (i=0; i<MAX; i++)
        suma=suma+ar[i];
    printf ("Suma=%ld\n",suma); return 0;
}