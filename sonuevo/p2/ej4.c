#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Estructura
struct fichero{

	int indice;
	char nombre_fich[50];
};

//Cabecera de funciones

void * hilo_Contador (void * p);

//Funcion principal
int main (int argc, char ** argv){
	int i;
	long contador;
	int suma_Final=0;
	struct fichero fich[argc-1];
	pthread_t hilo[argc-1];//Array de hebras
	for(i=0;i<(argc-1);i++){
		fich[i].indice=i;
		strcpy(fich[i].nombre_fich, argv[i+1]);
		pthread_create( &hilo[i],NULL,(void *)hilo_Contador,(void *) &fich[i]);
	}
	for(i=0;i<(argc-1);i++){
		pthread_join(hilo[i], (void **) &contador);
		printf("El hilo %d devuelve la suma: %ld\n",i,contador);
		suma_Final= suma_Final + contador;
	}

	printf("\n");
	
	printf("La suma final de todas las lineas de los ficheros leidos por los hilos es:%d\n",suma_Final);//con fich1.txt fich2.txt y fich3.txt da 23
	
return 0;
}

//Funciones auxiliares

void * hilo_Contador (void * p){

	struct fichero * aux= (struct fichero *) p;
	FILE * f;
	long contador=0;
	char linea[4000];
	if ( (f=fopen(aux->nombre_fich,"r") ) == NULL ){
	
		printf("Error al abrir el fichero.\n");
		exit(-1);
	}

	while (fgets(linea,4000,f)){ /* while ( fgets(linea,4000,f) != NULL)*/
	
		contador++;
	}
	fclose(f);
	
	printf("Hilo: %d. Numero de líneas:%ld.\n",aux->indice,contador);
	
	
	pthread_exit( (void *)contador);
}
