#include <pthread.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>

pthread_cond_t is_zero;

pthread_mutex_t mutex; // Condition variables needs a mutex. 
int shared_data = 5; // Or some other large number.

void *thread_function (void *arg) 
{
    pthread_mutex_lock(&mutex) ;
    while ( shared_data > 0) 
    {
        --shared_data ;
        printf("Thread - Decreasing shared_data... Value:%d\n",shared_data);
        sleep(1);
    }
    
    pthread_mutex_unlock(&mutex);
    printf("Thread, loop finished...\n");
    sleep(3);
    // Signal the condition. "shared_data" already is cero. This unlock the Main Thread printf("Sending signal to main() thread....shared_data = 0 !!!\n"); 
    pthread_cond_signal (&is_zero);
    return NULL;
}

int main (void)
{
    pthread_t thread_ID1;
    void *exit_status;
    
    pthread_cond_init (&is_zero , NULL) ;
    pthread_mutex_init (&mutex , NULL) ;
    
    pthread_create (&thread_ID1 ,NULL, thread_function , NULL) ;
    
    // Wait for the shared data to reach zero.
    pthread_mutex_lock(&mutex );

    printf("Main thread locking the mutex...\n"); //Main thread will be locked here.
    while ( shared_data != 0)
    {
        printf("I am the Main thread, shared_data is != 0. I am to sleep and unlock the mutex...\n");
        /* Elimina la espera activa, se desbloquea mutex y pasa a lista de bloqueado este hilo*/
        pthread_cond_wait (&is_zero, &mutex) ;
        /*Cuando se haga un pthread_cond_signal() asociado a is_zero, este hilo se desbloqueará, bloqueando a la vez el semáforo mutex, que se desbloquerá finalmente en el pthread_mutex_unlock(&mutex) que hay tres lineas más abajo*/
    }
    printf("Main awake - Value of shared_data: %d!!!\n", shared_data); 	
		
	pthread_mutex_unlock(&mutex) ;
    //To complete handle errors
    pthread_join( thread_ID1 , NULL) ; /*Destroy mutex and conditional variable*/
    pthread_mutex_destroy(&mutex) ; 
	pthread_cond_destroy (&is_zero) ; 
    exit(EXIT_SUCCESS);
}
