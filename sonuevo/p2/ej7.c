#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//Variables Globales
pthread_mutex_t mutex_acceso;

//Estructura
struct registro{
	int M;
	int *camisetas;
	int modelo;
};

//Cabecera
void *funcion_Cliente(void * p);
void *funcion_Proveedor(void *p);

//Funcion principal 
int main(int argc,char **argv){

	if(argc!=3){
	
		printf("Error en la sintaxis. ./a.out numProveedores numclientes.\n");
		exit(-1);
	
	}

	pthread_mutex_init(&mutex_acceso,NULL);
	
	
	srand(time(NULL));
	
	struct registro stock;
	int N,i;
	stock.M=atoi(argv[1]);
	
	stock.camisetas=(int *) calloc(stock.M,sizeof(int));
	if(stock.camisetas==NULL){
		printf("Error al reservar memoria en camisetas.\n");
		exit(-1);
	}
	
	
	N=atoi(argv[2]);
	
	pthread_t proveedor[stock.M],cliente[N];
	
	
	
	//Inicializamos el stock
	for(i=0;i<stock.M;i++){
	
		stock.camisetas[i]=i;
	}
	
	printf("El stock inicial es:\n");
	
	for(i=0;i<stock.M;i++){
	
	printf("Modelo[%d]=%d uds.\n",i,stock.camisetas[i]);
	}
	
	//Creacion hilos Proveedores
	for(i=0;i<stock.M;i++){
	
	pthread_create(&proveedor[stock.M], NULL,(void *) funcion_Proveedor, (void *) &stock); 

	}
	
	//Creacion hilos Clientes
	for(i=0;i<N;i++){
	
	pthread_create(&cliente[N], NULL,(void *) funcion_Cliente, (void *) &stock);
	}
	
	for(i=0;i<stock.M;i++){
	
	pthread_join(proveedor[stock.M],NULL); 

	}
	
	for(i=0;i<N;i++){
	
	pthread_join(cliente[N],NULL); 

	}
	
	//Imprimimos al final el stock
	
	printf("Stock final:\n-------------\n");
	
	for(i=0;i<stock.M;i++){
		
		printf("Modelo[%d]=%d uds.\n",i,stock.camisetas[i]);
	
	}
	
	pthread_mutex_destroy(&mutex_acceso);

return 0;
}




//Funciones
void *funcion_Cliente(void * p){
	
	struct registro * aux= (struct registro *) p;
	
	int numCamisetas;
	aux->modelo=rand()%aux->M;
	numCamisetas=rand()%10;
	
	pthread_mutex_lock(&mutex_acceso);
	
	printf("El cliente quiere comprar %d camisetas del modelo %d.\n",numCamisetas,aux->modelo);
	if( numCamisetas > aux->camisetas[aux->modelo] ){
	
		printf("Lo siento no disponemos de tantas camisetas por lo que el cliente comprara %d camisetas (el total de camisetas restantes).\n",aux->camisetas[aux->modelo]);
	
	aux->camisetas[aux->modelo]=0;
	}
	
	else{aux->camisetas[aux->modelo]-=numCamisetas;}
	
	pthread_mutex_unlock(&mutex_acceso);
	
	pthread_exit(NULL);
}

void *funcion_Proveedor(void *p){

	struct registro * aux= (struct registro *)p;
	int numCamisetas;
	aux->modelo=rand()%aux->M;
	numCamisetas=rand()%10;
	
	pthread_mutex_lock(&mutex_acceso);
	
	printf("El proveedor ha traido %d camisetas del modelo %d.\n",numCamisetas,aux->modelo);
	aux->camisetas[aux->modelo]+=numCamisetas;
	
	pthread_mutex_unlock(&mutex_acceso);
	
	pthread_exit(NULL);

}

