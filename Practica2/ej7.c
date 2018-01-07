//ej7.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mymutex;

struct camiseta{
	int modelo;
	int *camisetas;
	int M;
};

int main(int argc, char const *argv[])
{
	if(argc!=3){
	
		printf("Error en la sintaxis. ./a.out numProveedores numclientes.\n");
		exit(-1);
	
	}


	pthread_mutex_init(&mymutex , NULL);
	srand(time(NULL));

	struct camiseta stock;
	int N,i;

	stock.M=atoi(argv[1]);

	stock.cantidad=(int *) calloc(stock.M,sizeof(int));
	if(stock.cantidad=NULL){
		printf("Error al reservar memoria en camisetas.\n");
		exit(-1);
	}

	N=atoi(argv[2]);

	pthread_t provider[stock.M] , cliente[N];

	//inicializamos el stock

	for (int i = 0; i < stock.M; ++i)
	{
		stock.camisetas[i]=i;
	}

	printf("El stock inicial es:\n");

	for (int i = 0; i < stock.M; ++i)
	{
		printf("Modelo[%d]=%d uds.\n",i,stock.camisetas[i]);
	}




	return 0;
}
