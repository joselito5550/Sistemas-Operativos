#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

 #define TAM 20

void *cont_line_file(void *name){
  int *lines = (int *)malloc(sizeof(int));
  char *file_name = (char *)malloc(sizeof(char));
  file_name = (char *)name;
  char linea[FILENAME_MAX];
  FILE *f;
  *lines=0;
  //open the file in read mode
  f = fopen(file_name,"r");
  while(!feof(f)){
    *lines = *lines + 1;
    fgets(linea, FILENAME_MAX,f);
  }
  pthread_exit((void *)lines);
  fclose(f);
  free (lines);
  free (file_name);

}

//main program
int main(int argc, char **argv)
{
    if(argc == 1){
        printf("./ejer5 fichero.txt .. ficheron.txt\n");
        exit(0);
    }

    int i;
    pthread_t threads[TAM];

    //Create the threads with file parameters
    for(i=0;i<(argc-1);i++){
      pthread_create(&(threads[i]),NULL,(void *)cont_line_file,(void *)argv[i+1]);
    }
    int *lines;
    for(i=0;i<(argc-1);i++){
      pthread_join(threads[i],(void **)&lines);
      printf("Lineas del fichero %d ===> %d\n",i,*lines);
    }
}
