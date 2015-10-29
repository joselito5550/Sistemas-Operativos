#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>

int glob = 0; //GLOBAL VARIABLE
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //GLOBAL MUTEX

void * threadFunc(void *arg) /* Loop 'arg' times incrementing 'glob' */ 
{
    int loops = *((int *) arg); 
    int loc, j, s;
    
    for (j = 0; j < loops; j++) 
    {
        s = pthread_mutex_lock(&mtx); /*Lock the mutex*/
        if (s != 0)
            printf("mutex_lock error...\n");
        /*Critical Section */
        loc = glob;
        loc++;
        glob = loc;
        printf("Thread %ld increasing the global variable...\n", (unsigned long) pthread_self()); s = pthread_mutex_unlock(&mtx); /*Unlock the mutex*/
        if (s != 0)
            printf("mutex_unlock error...\n");
    }
    return NULL; 
}

int main(int argc, char *argv[]) 
{
    pthread_t t1, t2; 
    int loops, s;
    
    if(argc!=2) {
        printf("Ussage: ./a.out Number_of_loops\n");
        exit(EXIT_FAILURE); 
    }
    
    //loops = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000; 
    loops = atoi(argv[1]);
    
    s = pthread_create(&t1, NULL, threadFunc, &loops); 
    if (s != 0)
        printf("pthread_create error...\n");
    s = pthread_create(&t2, NULL, threadFunc, &loops); 
    if (s != 0)
        printf("pthread_create error...\n");
    
    printf("MAIN Thread, Stopping in the join call...\n"); 
    s = pthread_join(t1, NULL);
    if (s != 0)
        printf("pthread_join error...\n"); 
    s = pthread_join(t2, NULL);
    if (s != 0)
        printf("pthread_join error...\n");
    printf("MAIN Thread leaves join calls, the global variable is:%d\n", glob);
    exit(EXIT_SUCCESS); 
}