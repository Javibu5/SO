#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define NUM 5

void * message_print (void * ptr) 
{
    int error = 0;
    /* Desconexión del hilo cuando finalice. pthread_self() devuelve el ID de la hebra que invoca esta función. Se estudiará a continuación. */
    error = pthread_detach(pthread_self());
    /* Manejo del error si lo hubiera */
    //...
    printf("THREAD: This is the Message: %d\n", *(int *) ptr);
    pthread_exit(NULL); 
}

int main(void) 
{
    int error = 0;
    int i = 0;
    int j;
    int mess[NUM];
    
    /* Creación de un conjunto de hebras */ 
    pthread_t thr [NUM]; //Array de hebras
    
    for(i=0;i<NUM;i++) mess[i]=i+1;
    
    for(i = 0; i < NUM; i++) {
        error = pthread_create( &(thr[i]), NULL, message_print, (void *) &mess[i]); 
        /* Manejar el error */
        //...
    }
    
    printf("MAIN: This is the Message 0.\n"); 
    pthread_exit(NULL);
    printf("This line is not printed!!!\n");
}