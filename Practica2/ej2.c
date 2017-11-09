//ej2

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * Suma(int * n){

	int *x = (int *)malloc(sizeof(int));
	
	int n1 , n2;
	
	n1=rand() % 10;
	n2=rand() % 10;
	
	*x = n1 + n2;
	printf("Soy el hilo %d y mi suma es %d\n", *n , * x );

	pthread_exit(x);
}



int main()
{
	int n , suma = 0;
	int *valor_devuelto;



	printf("Introduce el número de hebras :\n");
	scanf("%d" , &n);



	srand(time(NULL));
	pthread_t thd[n];
	int i;
	for ( i = 0; i < n; ++i)
	{
		
		
		pthread_create (&thd[i], NULL, (void *) Suma, &i);
       	sleep(1);

	}


	for (int j = 0; j < n; ++j)
	{
		
		pthread_join(thd[j], (void **) &valor_devuelto);
        printf("El hilo %d ha devuelto el valor %d\n",j, *valor_devuelto);
        suma = suma + *valor_devuelto;
        
    }

    printf("%d\n", suma );
	   pthread_exit(NULL);
}