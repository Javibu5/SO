#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *message_print (void *ptr)
{
   int *y = malloc(sizeof(int)); // DEBE SER UN PUNTERI SINO DA ERROR EL PTHREAD_EXIT 
   *y = 10;	

   int error = 0;

   char *msg;

   /* Desconexión del hilo cuando finalice.
	   pthread_self() devuelve el ID de la hebra que invoca esta función.*/
   error = pthread_detach(pthread_self());
   if(error!=0)
       printf("Se ha producido un error en pthread_detach()\n");
   // Complételo con las macros de error convenientes
   //...

   msg = ptr;
   printf("Soy la hebra: %s\n", msg);
   pthread_exit(y);
}

int main(void)
{
   int error = 0;
   char mess[] = "Esto es una prueba...";
   pthread_t thr;
   void *ret;    // DEBE SER UN void * SINO DA ERROR EL JOIN 
   int aux = 7;

   ret = &aux;

   error = pthread_create( &thr, NULL, message_print, mess);
   /* Manejar el error */
   //...

   printf("Soy el main():%s\n", mess);

  /* Si el join se ejecuta una vez haya terminado la hebra detach, daría un error y el valor de retorno
   sería 7, pues ya se habría liberado el estado, variables y demás, de la hebra detach, en caso contrario,
   si el join se ejecuta antes de que termine la hebra detach, el join no dará error y devolvería
   el valor 10. De ahí que no se deba utilizar el join con una hebra detach para evitar inconsistencias. */
  
   // sleep(3);	 
   error=pthread_join(thr,&ret);
  
   if(error!=0)
      printf("Se ha producido un error en pthread_join()\n");
	
   int result = *(int *)ret;	
   printf("Soy el main(), valor de retorno de la hebra: %d\n",result);
   pthread_exit(NULL);
}


