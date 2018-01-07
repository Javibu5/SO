#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Variable global
char buffer[1024];
pthread_mutex_t mutex_acceso;
int numlineas=0;
int numFich,indice=0;

//Cabeceras
void * lee_original(void *p);
void * escribe_copia(void * p);
void contarLineas(char * fichOriginal);

//Funcion Principal
int main(int argc,char ** argv){

	int i;
	char N[5];
	
	if(argc!=3){
	
		printf("Error en la sintaxis. ./a.out nombrefich numcopias \n");
		exit(-1);
	}
	//Guardamos en variables los valores pasados por argumentos
	char fichOriginal[strlen(argv[1])],fichaux[strlen(argv[1])+1];
	
	numFich=atoi(argv[2]);
	strcpy(fichOriginal,argv[1]);
	printf("numFich=%d\n",numFich);
	printf("fichOriginal=%s\n",fichOriginal);
	strncpy(fichaux,fichOriginal,strlen(fichOriginal)-4);
	printf("fichaux=%s\n",fichaux);
	
	//Inicializamos el semaforo mutex
	pthread_mutex_init(&mutex_acceso,NULL);
	
	//Tambien inicializamos una vez sabemos el numero de copias, los hilos y el vector con los nombres de cada fichero
	pthread_t hilo_Original,hilo_Copia[numFich];
	char nombre_Copia[100][100];
	
	//Damos el nombre de fichero a cada uno de los ficheros copia		
	
	for(i=0;i<numFich;i++){
		sprintf(N,"%d",i);
		printf("N=%s.\n",N);
		
		strcpy(nombre_Copia[i],fichaux);
		strcat(nombre_Copia[i],N);
		strcat(nombre_Copia[i],".txt");
		printf("nombre_Copia[i]=%s\n",nombre_Copia[i]);
	}
	//Contamos cuantas lineas tiene el fichero original
	contarLineas(fichOriginal);
	printf("numlineas=%d.\n",numlineas);
	
	pthread_create(&hilo_Original,NULL,(void*)lee_original,(void *) fichOriginal);
	
	
	for(i=0;i<numFich;i++){
	
		pthread_create(&hilo_Copia[i],NULL,(void*)escribe_copia,(void *)nombre_Copia[i]);
	}

	pthread_join(hilo_Original,NULL);
	
	for(i=0;i<numFich;i++){

		pthread_join(hilo_Copia[i],NULL);
	}
	
	pthread_mutex_destroy(&mutex_acceso);
	
return 0;
}

//Funciones auxiliares
void contarLineas(char * fichOriginal){

	FILE * f;
	int i;

	f=fopen(fichOriginal,"r");
	if(f==NULL){

		printf("Error al abrir fichero(Funcion contarLineas).\n");
		exit(-1);
	}
	
	while(fgets(buffer,1024,f)!=NULL){numlineas++;}
	fclose(f); 
}

void * lee_original(void *p){

	char * aux=(char *) p;
	FILE * f;
	
	f=fopen(aux,"r");
	if(f==NULL){
		printf("Error al abrir el fichero %s.\n",aux);
		exit(-1);
	}
	
	numlineas++;
	
	while(numlineas!=0){
		pthread_mutex_lock(&mutex_acceso);	
		if(indice==0){
			fgets(buffer,1024,f);
			indice=0-numFich;
			numlineas--;
			printf("buffer=%s\n",buffer);
		}	
		pthread_mutex_unlock(&mutex_acceso);
	}
	
	
	
	fclose(f);	
	pthread_exit(NULL);
}

void * escribe_copia(void * p){

	char * aux=(char *)p;
	FILE * f;
	
	f=fopen(aux,"a");
	if(f==NULL){
		printf("Error al abrir el fichero %s.\n",aux);
		exit(-1);
	}
	
	while(numlineas!=0){
		pthread_mutex_lock(&mutex_acceso);
		if(indice!=0){
			fputs(buffer,f);
			indice++;
		}	
		pthread_mutex_unlock(&mutex_acceso);
	}
	fclose(f);
	pthread_exit(NULL);
}
