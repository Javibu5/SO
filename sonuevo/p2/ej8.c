#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//Variables globales
int buffer[5]={0,0,0,0,0};
pthread_mutex_t mutex_acceso;

//Estructura registro
struct registro{

int numP,numC,nEle;

};
//Cabeceras
void * Consumidor (void * p);
void * Productor (void * p);

//Funcion principal
int main(int argc,char **argv ){

	if(argc!=3){
		printf("Error en la sintaxis. ./a.out Productores Consumidores \n");
		exit(-1);
	}
	
	pthread_mutex_init(&mutex_acceso,NULL);
	
	srand(time(NULL));
	int i;
	struct registro r;
	r.numP=atoi(argv[1]);
	r.numC=atoi(argv[2]);
	
	pthread_t p[r.numP],c[r.numC];
	
	printf("-------------\nBUFFER INICIO:\n-------------\n");
	for(i=0;i<5;i++){
	
		printf("buffer[%d]=%d\n",i,buffer[i]);
	}
	
	
	//Creamos hilos productores
	for (i=0;i<r.numP;i++){
	
		pthread_create(&p[i],NULL,(void *) Productor, (void *) &r);
	
	}
	
	//Creamos hilos consumidores
	for(i=0;i<r.numC;i++){
	
		pthread_create(&c[i],NULL, (void *) Consumidor, (void *) &r);
	
	}
	
	//Esperamos hilos productores
	for(i=0;i<r.numP;i++){
	
		pthread_join(p[i],NULL);

	}
	
	//Esperamos hilos consumidores
	for(i=0;i<r.numC;i++){
	
		pthread_join(c[i],NULL);
	
	}
	
	printf("-------------\nBUFFER FINAL:\n-------------\n");
	for(i=0;i<5;i++){
	
		printf("buffer[%d]=%d\n",i,buffer[i]);
	}
	
	
	pthread_mutex_destroy(&mutex_acceso);
return 0;
}

//Funciones
void * Consumidor(void * p){

	struct registro * aux=(struct registro *) p;
	
	aux->nEle=rand()%5;
	
	pthread_mutex_lock(&mutex_acceso);
	
	printf("Soy un cliente que va a comprar una unidad %d. ",aux->nEle);
		
	if(buffer[aux->nEle]==0){
	
		printf("Pero no puedo ya que quedan %d unidades del tipo %d, asi que me voy.\n",buffer[aux->nEle],aux->nEle);
	}

	else{
		printf("Quedan %d uds. aún y me voy a llevar una,",buffer[aux->nEle]);
		buffer[aux->nEle]--;
		printf("Ahora quedan %d unidades del tipo %d.\n",buffer[aux->nEle],aux->nEle);
	}

	pthread_mutex_unlock(&mutex_acceso);
	
	pthread_exit(NULL);
	
}

void * Productor (void * p){

	struct registro * aux=(struct registro *) p;
	
	int i;
	
	pthread_mutex_lock(&mutex_acceso);
	
	printf("Soy un productor y traigo una unidad de cada tipo.Antes habia:\n");
		
	for(i=0;i<5;i++){
		printf("buffer[%d]=%d\n",i,buffer[i]);
		buffer[i]++;
	}
	
	printf("Y ahora hay:\n");
	for(i=0;i<5;i++){
	
		printf("buffer[%d]=%d\n",i,buffer[i]);
	}
	
	pthread_mutex_unlock(&mutex_acceso);
	
	pthread_exit(NULL);
}
