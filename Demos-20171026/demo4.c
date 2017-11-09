#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

void *mifuncion(int *arg) 
{
    printf("Hilo hijo ejecutando...\n");
	printf("Hilo hijo: arg1= %d arg2= %d\n", arg[0], arg[1]);
    printf("Hilo hijo finalizando....\n"); 
    sleep(3);
    pthread_exit(NULL);
}

int main (void) {
    pthread_t tid; int misargs[2];
    misargs[0] = -5; misargs[1] = -6;
    printf("Se va a crear un hilo...\n");
    pthread_create(&tid, NULL, (void*) mifuncion, &misargs);
    printf("Hilo creado. Esperando su finalizacion con pthread_join()...\n");
    /*Si comentamos la siguiente linea, puede que a la hebra no le de tiempo a ejecutarse ni siquiera parcialmente,
     de manera que el main() terminará y con el todas las hebras asociadas a este proceso*/ 
    pthread_join(tid, NULL);
    printf("Proceso principal finalizado...\n");
    exit(EXIT_SUCCESS);
}
