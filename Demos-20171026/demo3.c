#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

void *mifuncion(int *arg) 
{
    printf("Hilo hijo ejecutando...\n");
    printf("Hilo hijo: arg1= %d arg2= %d\n", arg[0], arg[1]);
    printf("Hilo hijo finalizando....\n");
    /* Esta funcion no devuelve nada, por tanto no se podra� recoger nada con un join(). Por defecto, si no se incluye se hace implicitamente un pthread_exit(NULL); */
    pthread_exit(NULL);
}

int main () 
{
    pthread_t tid;
    //Vector de enteros que vamos a pasar como parámetro a una hebra haciendo casting a void * 
    int misargs[2];
    misargs[0] = -5;
    misargs[1] = -6;
    printf("Se va a crear un hilo...\n");
    pthread_create(&tid, NULL, (void *)mifuncion, &misargs);
    printf("Hilo creado. Esperando su finalizacion con pthread_join()...\n");
    /*Si comentamos la siguiente linea, puede que a la hebra no le de tiempo a ejecutarse ni siquiera parcialmente,
     de manera que el main() terminará y con el todas las hebras asociadas a este proceso*/ 
    pthread_join(tid, NULL);
    printf("Hilo finalizado...\n"); 
}
