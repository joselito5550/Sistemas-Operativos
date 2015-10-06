#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void controlador(){
  printf("He recibido la señal SIGUSR1 del otro programa\n");
}

int main(){
  printf("Mi pid es: %d\n",getpid());
  signal(SIGUSR1,controlador);
  while(1){
    pause();
  }
}
