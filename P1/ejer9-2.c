#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int main(int argc, char **argv){
    pid_t pid = atoi(argv[1]);
    int i=0;
    for(i=0;i<8;i++){
      kill(pid,SIGUSR1);
      sleep(3);
    }
    kill(pid,SIGINT);
    return 0;
}
