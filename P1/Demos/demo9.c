/* alarm.c - Implementa un sleep con la señal de alarma */

#include	<signal.h>
#include	<stdio.h>
#include	<unistd.h>
#include <stdlib.h>

static void sig_alrm(int signo)
{
	return;	/* nothing to do, just return to wake up the pause */
}

unsigned int sleep1(unsigned int nsecs)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)  
		return(nsecs);
	alarm(nsecs);		/* start the timer */
	pause();			/* next caught signal wakes us up */
	return(alarm(0));	/* turn off timer, return unslept time */
}

int main ()
{
    printf ("Una alarma en 3 segundos.\n");
    sleep1(3);
    printf ("Terminado el primer sleep...\n");
    sleep1(2);
    printf ("Terminado el segundo sleep...\n");
}
