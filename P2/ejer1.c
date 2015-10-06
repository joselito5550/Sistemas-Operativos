#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#define TAM 100

/*Función que se asignará a los hilos que se creen. Recibe un puntero a estructura */
void *show_messages (void * mensa)
{
  int i=0;
  char* word = (char *)mensa;
  for(i=0;i<strlen(word);i++){
    sleep(1);
    printf("%c\n",word[i]);
    sleep(1);
  }
  pthread_exit(NULL); //Fin de la hebra sin devolver nada
}

int main(int argc, char **argv)
{
  //Check
  if(argc!=3){
    printf("./ejer1 first_word second_word\n");
    exit(-1);
  }

	//Declaración de dos hebras, hilos o procesos ligeros. NO CREACION
	pthread_t thd1, thd2;

  //Create the param to the threads
  char param1[TAM];
  char param2[TAM];

  strcpy(param1,argv[1]);
  strcpy(param2,argv[2]);

	/*Creamos dos hilos. La función la pasaremos como (void *) nombreFuncion. Es decir,
  hacemos un casting a (void *), aunque por defecto no es necesario, ya que el nombre
  de una función es su dirección de memoria. También es importante realizar esto con la
  dirección de memoria de la variable que contiene los parámetros que se le pasan
  a la función */
	pthread_create(&thd1, NULL, (void *)show_messages, (void *) &param1);
	pthread_create(&thd2, NULL, (void *)show_messages, (void *) &param2);

	/*Esperamos la finalización de los hilos. Si la función devolviera algo habría que recogerlo
  con el segundo argumento, que en este caso esta a NULL. Cuando el segundo
  argumento no es NULL, se recogen los resultados que vienen de pthread_exit(), que se
   explicará en las siguientes demos.*/
	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);

	/*Si no se ponen estos join() en el programa principal y simplemente lanzamos los
   dos hilos y finalizamos, lo más probable es que los hilos no lleguen a ejecutarse
   completamente o incluso que no lleguen ni a empezar antes de que el programa
    principal termine.*/
	printf("Han finalizado las threads.\n");
	exit(EXIT_SUCCESS);
}
