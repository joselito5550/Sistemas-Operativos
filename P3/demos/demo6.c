#include <pthread.h> 
#include <semaphore.h>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>

//Programa sin el necesario tratamiento de errores

#define NITER 100 
int count = 0;
sem_t mutex;

void * ThreadAdd(void *a) 
{
    int i, tmp,p;
    for(i = 0; i < NITER; i++) 
    {
        p= sem_wait(&mutex);
        tmp = count; /* copy the global count locally */
        tmp = tmp+1; /* increment the local copy */
        count = tmp; /* store the local value into the global count */
        sem_post(&mutex);
    } 
    pthread_exit(NULL);
}

int main(int argc, char * argv[]) 
{
    //inicializamos nuestro semáforo a 1
    //y el cero indica que el semáforo solo
    //estara disponible para este main() y sus hilos(). 
    sem_init(&mutex, 0, 1);
    pthread_t tid1, tid2;
    
    //Note que podría hacer esto con un bucle for() 
    if(pthread_create(&tid1, NULL, ThreadAdd, NULL)) 
    {
        printf("\n ERROR creating thread 1");
        exit(EXIT_FAILURE); 
    }
    if(pthread_create(&tid2, NULL, ThreadAdd, NULL)) 
    {
        printf("\n ERROR creating thread 2");
        exit(EXIT_FAILURE); 
    }
    //Note que podría hacer esto con un bucle for() 
    if(pthread_join(tid1, NULL)) /* wait for the thread 1 to finish */ 
    {
        printf("\n ERROR joining thread");
        exit(EXIT_FAILURE); 
    }
    if(pthread_join(tid2, NULL)) /* wait for the thread 2 to finish */ 
    {
        printf("\n ERROR joining thread");
        exit(EXIT_FAILURE); 
    }
    if ( (count< (2 * NITER)) || (count>(2 * NITER)) )
        printf("\n BOOM! count is [%d], should be %d\n", count, 2*NITER);
    else
        printf("\n OK! count is [%d] \n", count);
    pthread_exit(NULL); 
}
