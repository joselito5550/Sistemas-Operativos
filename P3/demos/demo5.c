/******************************************* 
 Modified from Michael Kerrisk's code, 2014. 
 ********************************************/ 
#include <pthread.h>
#include <stdlib.h> 
#include <stdio.h>

typedef enum {FALSE=0, TRUE=1} booleano; 
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
int avail = 0;

void * threadFunc(void *arg) 
{
    int cnt = atoi((char *) arg); int s, j;
    for (j = 0; j < cnt; j++)
    {
        //lock mutex
        s = pthread_mutex_lock(&mtx);
        if (s != 0)
            printf("mutex_lock error...\n");
        /* Let consumer know another unit is available */
        avail++;
        printf("avail variable increased by thread %lu, avail=%d\n", (unsigned long) pthread_self(),avail); //Unlock mutex
        s = pthread_mutex_unlock(&mtx);
        if (s != 0)
            printf("mutex_unlock error...\n");
        /* Wake sleeping consumer */
        s = pthread_cond_signal(&cond);
        if (s != 0)
            printf("pthread_cond_signal error...\n");
        printf("Sending cond_signal from thread %lu...\n", (unsigned long) pthread_self()); 
    }
    return NULL; 
}

int main(int argc, char *argv[]) 
{
    pthread_t tid;
    int s, j;
    int totRequired; /* Total number of units that all threads will produce */ 
    int numConsumed; /* Total units so far consumed */
    booleano done;
    
    if(argc<=3) {
        printf("Ussage: ./a.out Number_of_increasing_for_thread1 Number_of_increasing_for_thread2 Number_of_increasing_for_threadN\n");
        exit(EXIT_FAILURE); 
    }
    /* Create all threads */ totRequired = 0;
    for (j = 1; j < argc; j++) {
        totRequired += atoi(argv[j]);
        s = pthread_create(&tid, NULL, threadFunc, argv[j]); 
		if (s != 0)
            printf("pthread_create error...\n");
    }
    /* Loop to consume available units */ numConsumed = 0;
    done = FALSE;
    for (;;) //Continuous simulation
    {
        //lock mutex
       
        s = pthread_mutex_lock(&mtx);
        if (s != 0)
            printf("mutex_lock error...\n");
        while (avail == 0) 
        {
            /* Wait for something to consume */
            printf("Main entering in pthread_cond_wait() call.... Main will be locked by the planner!!\n");
            s = pthread_cond_wait(&cond, &mtx);
            if (s != 0)
                   printf("pthread_cond_wait error...\n");
            printf("Sleeping time finished. Main state is Running. No Unproductive time while avail is <=0!!\n");
        }
        while (avail > 0) /* Consume all available units */ 
        {
            /* Do something with produced unit */
            numConsumed ++;
            avail--;
            printf("Main, numConsumed=%d\n", numConsumed); 
            if((numConsumed >= totRequired)) 
                done=TRUE;
            else done=FALSE;
            //done = numConsumed >= totRequired;
        }
        //Unlock mutex
        s = pthread_mutex_unlock(&mtx); 
        if (s != 0)
            printf("mutex_unlock error...\n");
        if (done) 
        {
            printf("Exiting...All produced items have been consumed\n");
            break; 
        }
        /* Perhaps do other work here that does not require mutex lock */ 
                      
    }
    exit(EXIT_SUCCESS); 
}
                      
