//ej1

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>


void *hiloMensaje (char *palabra);

int main()
{
	
pthread_t thd1 , thd2;



pthread_create (&thd1 , NULL , (void*)hiloMensaje , "hola");


pthread_create (&thd2 , NULL , (void*)hiloMensaje , "mundo");

pthread_join(thd1, NULL); 

    pthread_join(thd2, NULL);

    printf("Han finalizado los thread.\n");

    exit(EXIT_SUCCESS); 



}



void *hiloMensaje (char *palabra){

int largo = strlen(palabra);

for (int i = 0; i < largo; ++i)
{
printf("%c \n", palabra[i] );
sleep(1);
}


}