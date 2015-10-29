#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>

//Programa sin el necesario tratamiento de errores
/* datos a leer y escribir. Podría usar también un while(){} */ 
#define DATOS_A_ESCRIBIR 10
#define NUM_LECTORES 2
#define NUM_ESCRITORES 2
/* Recurso. No hay buffer solo se puede escribir en o leer de una variable. Una mejora interesante sería hacer un buffer donde pudieran escribir y leer los escritores y lectores sin causar incoherencia en los datos*/

int dato = 0;
int n_lectores = 0; /* numero de lectores */
sem_t sem_lec; /* controlar el acceso n_lectores */

sem_t mutex; /* controlar el acceso a dato */

void * Lector(void * arg) {
    //Complete el manejo de errores
    //....
    int i=0;
    for(i=0; i < DATOS_A_ESCRIBIR; i++ ) 
    {
        sem_wait(&sem_lec); 
        
        n_lectores = n_lectores + 1; 
        if (n_lectores == 1)
            sem_wait(&mutex); 
        sem_post(&sem_lec);
        
        printf("Lector %lu y leo %d\n", (unsigned long)pthread_self(), dato); /* leer dato */
        
        sem_wait(&sem_lec); 
        n_lectores = n_lectores - 1; 
        if (n_lectores == 0) 
            sem_post(&mutex); 
        sem_post(&sem_lec);
        
    }    
    pthread_exit(NULL); 
}

void * Escritor(void * arg) {
    //Complete el manejo de errores
    //....
    int i=0;
    for(i=0; i < DATOS_A_ESCRIBIR; i++ ) 
    {
        sem_wait(&mutex); //No más de un escritor a la vez
        dato = dato + 1; /* modificar el recurso */
        printf("Escritor %lu y escribo %d\n", (unsigned long) pthread_self(), dato); 
        sem_post(&mutex);
    }
    pthread_exit(NULL); 
}

int main(void) 
{
    //Complete el manejo de errores en el main() //....
    int i;
    pthread_t thlectores[NUM_LECTORES], thescritores[NUM_ESCRITORES];
    sem_init(&mutex, 0, 1); 
    sem_init(&sem_lec, 0, 1);
    
    for(i=0; i < NUM_LECTORES; i++ ) 
        pthread_create(&thlectores[i], NULL, Lector, NULL); 
    for(i=0; i < NUM_ESCRITORES; i++ ) 
        pthread_create(&thescritores[i], NULL, Escritor, NULL); 
    
    for(i=0; i < NUM_LECTORES; i++ )
        pthread_join(thlectores[i], NULL);
    for(i=0; i < NUM_ESCRITORES; i++ ) 
        pthread_join(thescritores[i], NULL);
    
    /* eliminar todos los semaforos */ 
    sem_destroy(&mutex); 
    sem_destroy(&sem_lec);
}
