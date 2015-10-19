#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define TAM 10

void *FsV(void *parametro);

struct infoReparto
{
  int *vector;
  int hasta;
  int desde;

};

int main(int argc, char *argv[])
{
  int vector[TAM];

  pthread_t hebras[TAM];

  struct infoReparto reparto;
  struct infoReparto repartoHebras[TAM];

  int nHebras;
  int desde;
  int hasta;
  int suma=0;
  int error;
  int i;

  int *sumaVector;


  srand(time(NULL));

  nHebras=atoi(argv[1]);

  if(argc != 2)
  {
    printf("Introduzca el formato ./eje3.exe 'nºhebras'\n");

  }

  for(i=0; i<10; i++)
  {
    vector[i]=rand()%10;

    printf("posicion V[i]:%d\n", vector[i]);
    suma=suma+vector[i];
  }

  printf("suma:%d\n", suma);
  suma=0;

  reparto.vector=vector;
  desde=0;

  hasta=(int)(10/nHebras);

  for(i=0; i<nHebras; i++)
  {
    reparto.desde=desde;

    if(i == (nHebras-1))
    {
      reparto.hasta=10;

    }else
      {
        reparto.hasta=desde+hasta;
      }

    repartoHebras[i]=reparto;

    desde=reparto.hasta;

    error=pthread_create(&(hebras[i]), NULL, (void *)FsV, (void *)&repartoHebras[i]);

    switch(error)
    {
      case 0:
        printf("Se ha creado la hebra con id:%lu correctamente\n", (unsigned long int)hebras[i]);
        printf("Tiene que realizar la suma desde:%d, hasta:%d\n", repartoHebras[i].desde, repartoHebras[i].hasta-1);
        break;

      case EAGAIN:
        printf("Se ha producido el error EAGAIN por falta de recursos o por alcanzar el maximo numero de hebras\n");
        break;

      case EINVAL:
        printf("Se produjo el error EINVAL, valores attr incorrectos\n");
        break;

      case EPERM:
        printf("Se produjo el error EPERM, sin privilegios para la configuracion o attr\n");
        break;

    }
  }

  for(i=0; i<nHebras; i++)
  {
    error=pthread_join(hebras[i], (void **)&sumaVector);

    switch(error)
    {
      case 0:
        printf("Termino correctamente la hebra con id:%lu\n", (unsigned long int)hebras[i]);
        printf("Y devolvio el valor %d\n", *sumaVector);

        suma=suma+(*sumaVector);
        break;

      case EDEADLK:
        printf("Se quiso hacer un join a si mismo\n");
        break;

      case EINVAL:
        printf("Se produjo el error EINVAl, la hebra ha sido detached o otra hebra esta esperando a que termine\n");
        break;

      case ESRCH:
        printf("Se produjo el erro ESRCH, la hebra no existe\n");
        break;

    }
  }

  printf("El resultado de la suma es:%d\n", suma);
  printf("Finalizacion correcta\n");



  exit(EXIT_SUCCESS);
}

void *FsV(void *parametro)
{
  int *suma;

  struct infoReparto *reparto;

  int i;

  suma=(int*)malloc(sizeof(int));

  if(suma == NULL)
  {
    printf("Hubo un error en la reserva de memoria dinamica para suma\n");

    exit(EXIT_FAILURE);
  }

  reparto=(struct infoReparto *)parametro;

  for(i=(*reparto).desde; i<(*reparto).hasta; i++)
  {
    *suma=*suma+(*reparto).vector[i];
  }

  pthread_exit((void *)suma);
}
