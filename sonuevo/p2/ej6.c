#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//Estructura cuentaHilos
struct cuentaHilos{

	int contador;
	int indice;


};

//Funcion auxiliar hebra
void *hebra (void *p);

//Funcion principal

int main (int argc, char **argv){

	if(argc!=2){
		
		printf("Error en la sintaxis. /a.out numhilos\n");
		exit(-1);		
	}
	struct cuentaHilos c;
	int N,i;
	pthread_t hilo[N];
	
	N=atoi(argv[1]);
	printf("Se crearan %d hilos.\n",N);
	c.contador=0;
	for(i=0;i<N;i++){
		c.indice=i;
		pthread_create(&hilo[i],NULL,(void *) hebra,(void *) &c);
	}

	for(i=0;i<N;i++){
	
		pthread_join(hilo[i], (void **) &c.contador);
		printf("contador:%d\n",c.contador);
	}

	printf("Contador final:%d\n",c.contador);
	

return 0;
}

//Funcion hebra

void *hebra (void *p){

	struct cuentaHilos *aux= (struct cuentaHilos *) p;
	int i;
	
	for(i=0;i<100;i++){aux->contador++;}

	pthread_exit( (void *)aux->contador);
}
