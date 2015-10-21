#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

 #define TAM 20

void *conversor(void *name){

  int i;
  char *mp3_name = (char *)malloc(sizeof(char));
  char *video_name = (char *)malloc(sizeof(char));
  video_name=(char *)name;
  char *comando = (char *)malloc(sizeof(char));

  for(i=0;i<(strlen(video_name)-4);i++){
    mp3_name[i]=video_name[i];
  }
  mp3_name[i]='\0';
  strcat(mp3_name,".mp3");

  sprintf(comando, "ffmpeg -i %s -f mp3 -ab 192000 -ar 48000 -vn %s", video_name, mp3_name);
  system(comando);

  free(video_name);
  free(mp3_name);
  free(comando);
}

int main(int argc, char **argv)
{
    if(argc != 3){
        printf("./ejer4 name_video1 name_video2\n");
        exit(0);
    }

    char *name_video1 = argv[1];
    char *name_video2 = argv[2];

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1,NULL,(void *)conversor,(void *)name_video1);
    pthread_create(&thread_2,NULL,(void *)conversor,(void *)name_video2);

    pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);

}
