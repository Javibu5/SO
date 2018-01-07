#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//estructura palabra
struct palabra{

char pal[15];
int tam;
};

//cabecera
void *hiloCadena (void * p);

//funcion principal
int main(int argc,char **argv){

	if(argc!=3){
		printf("ERROR en la sintaxis. %s cadena1 cadena2\n",argv[0]);
		exit(-1);
	}
	
	//inicializamos los hilos
	pthread_t thd1, thd2;
	
	//declaramos los hilos
	struct palabra p1,p2;
	strcpy(p1.pal,argv[1]);
	strcpy(p2.pal,argv[2]);
	p1.tam=strlen(p1.pal);
	p2.tam=strlen(p2.pal);
	//creamos los hilos
	pthread_create(&thd1, NULL,(void *) hiloCadena, (void*) &p1);
	pthread_create(&thd2, NULL,(void *) hiloCadena,(void*) &p2);
	
	
	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);
	
	printf("\n");
	



return 0;
}


//funciones

void *hiloCadena (void * p){

	int i;
	struct palabra* aux= (struct palabra *)p;
	
	for (i=0;i<strlen(aux->pal);i++){
	
		printf("%c\n",aux->pal[i]);
		sleep(1);
	}
	pthread_exit(NULL);
}

