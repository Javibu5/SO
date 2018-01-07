#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>

void * message_print (void * ptr) 
{
    int error = 0; 
    char *msg;
    /* Desconexión del hilo cuando finalice. pthread_self() devuelve el ID de la hebra que invoca esta función. Se estudiará a continuación. */
    error = pthread_detach(pthread_self());
    /* Manejar el error */ //...
    msg = (char *) ptr;
    printf("THREAD: This is the Message %s\n", msg); 
    pthread_exit(NULL);
}

int main(void) {
    int error = 0;
    size_t i = 0;
    char mess[] = "This is a test"; 
    int thread_no = 5;
    
    /* Creación de un conjunto de hebras */ 
    pthread_t thr[5]; //Array de hebras 
    for(i = 0; i < thread_no; i++)
    {
        error = pthread_create( &(thr[i]), NULL, message_print, (void *) mess); 
        /* Manejar el error */
        //...
    }
    printf("MAIN: Thread Message: %s\n", mess); 
    // La siguiente línea permite que el proceso o hebra principal espere a que 
    //terminen hebras que se han invocado a pthread_detach().
    pthread_exit(NULL);
}