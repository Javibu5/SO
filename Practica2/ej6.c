//ej 6

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void * contador(int * a){

	for (int k = 0; k < 100; ++k)
	{
		(*a) = 1 + (*a);
	}
}
	



int main()
{

	int N;
	int contador = 0;
	pthread_t thd[100];

	printf("Dime el numero de hilos que quieres crear\n");
	scanf("%d" , N);


	

	for (int i = 0; i < N; ++i)
	{
		printf("llega hasta aquiç\n");
		pthread_create(&thd[N] , NULL , (void*) contador , &contador);
	}

	for (int j = 0; j < N; ++j)
	{
		pthread_join(thd[j], NULL);

	}
	
	printf("El contador vale %d\n", contador);
	
	return 0;
}