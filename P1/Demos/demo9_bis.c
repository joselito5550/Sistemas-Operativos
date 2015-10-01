/* alarm.c - Implementa un sleep con la señal de alarma */

#include	<signal.h>
#include	<stdio.h>
#include	<unistd.h>
#include <stdlib.h>
#include <errno.h>

static void sig_alrm(int signo)
{
	printf("In the sig_alrm function!!!\n");
	printf("Value of signo:%d\n",signo);
	return;	/* nothing to do, just return to wake up the pause */
}

unsigned int f1(unsigned int nsecs)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
	{
		perror("Signal error");
   	printf("errno value= %d\n", errno);  
		exit(EXIT_FAILURE);
	}
	alarm(nsecs);		/* start the timer */
	pause();			/* pause - suspend the thread until a signal is received */ 
}

int main ()
{
    printf ("Una alarma en 3 segundos.\n");
    f1(3);
    printf ("Terminado el primer sleep...\n");
    f1(2);
    printf ("Terminado el segundo sleep...\n");
}
