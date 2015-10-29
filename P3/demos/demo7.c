#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

//Programa sin el necesario tratamiento de errores
//Semáforo s1 para lo impares y s2 para los pares. 
sem_t s1, s2;
//Sección crítica
int num=0, suma=0;

void *p1(void * a)
{
    int i;
    for (i=1; i<20; i++)
    {
        sem_wait (&s1); /*Cuando haya que sumar un impar se bloqueará aquí hasta que termine P2. La primera vez que entra no se bloquea, esta inicializado a 1*/
        if (i%2) /*Si el resultado del modulo es distinto de cero (cierto en C) es que es impar. */ 
        {
            num=i;
            printf ("HILO1: Número impar %d. Desbloqueando a HILO 2\n", i); sem_post (&s2); //Si p2() está esperando en s2, P2 se desbloqueará.
        }
        else //Si el resultado del modulo es cero el numero es par.
            sem_post (&s1); /*Incrementa s1, el siguiente numero será impar y
                             debe entrar en sección critica y no quedarse bloqueado en el wait(). */
    }
    pthread_exit(NULL); 
}

void *p2(void * a)
{
    int i;
    for (i=0; i<10; i++) {
        /*Se queda esperando cuando el número es par y lo tiene que desbloquear P1 cuando encuentre un impar, ya que “num” tendra el valor impar a sumar*/
        sem_wait (&s2);
        printf ("HILO2: Suma actual = %d + %d\n", suma, num);
        suma = suma+num;
        /*Cuando haya sumado un impar desbloqueará a P1() incrementando s1 para que busque el siguiente impar. P1 se encontrará esperando a que P2 haga la suma antes de poder volver a entrar en la sección crítica*/
        sem_post (&s1);
    }
    pthread_exit(NULL); 
}

int main() 
{
    int error1, error2;
    pthread_t h1, h2;
    sem_init(&s2, 0, 0); //Semáforo inicializado a 0 
    sem_init(&s1, 0, 1); //Semáforo inicializado a 1 
    
    //Note que podría hacer esto con un bucle for() 
    pthread_create(&h1, NULL, p1, NULL); 
    pthread_create(&h2, NULL, p2, NULL); 
    //Complete el control de errores
    // ...
    pthread_join (h1, NULL);
    pthread_join (h2, NULL);
    //Complete el control de errores
    // ...
    printf ("Main() - La suma es %d\n", suma);
    return 0;
}
