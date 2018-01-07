//ej 6

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct cuentaHilos{
	int contador;
	int indice;
};


void * contador(void * a);
	



int main()
{

	int N;
	pthread_t thd[100];
	struct cuentaHilos c;
	c.contador = 0;
	printf("Dime el numero de hilos que quieres crear\n");

	scanf("%d" , &N);


	

	for (int i = 0; i < N; ++i)
	{
		pthread_create(&thd[N] , NULL , (void*) contador , (void*)&c.contador);
		
	}

	for (int j = 0; j < N; ++j)
	{
		pthread_join(thd[j], (void**) &c.contador );
		printf("el contador %d :%d\n", j , c.contador );

	}
	
	printf("El contador vale %d\n", c.contador);
	
	return 0;
}

void * contador(void * a){
	struct cuentaHilos *aux = (struct cuentaHilos *) a;
	int i;
	for (int i = 0; i<100; ++i)
	{
		aux->contador++;
	}

pthread_exit((void*)aux->contador);
}