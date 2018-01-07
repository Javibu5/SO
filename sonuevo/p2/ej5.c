#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//estructura cuenta

struct cuenta{

	int indice;
	int *vector;
	int **matriz;
	int nEle;
};

//cabecera

void *hebra (void * p);

//funcion principal
int main(){

	srand(time(NULL));
	int *Vector, **Matriz;
	int nEle=3;
	int i,j;
	int Vector_Resultado[nEle];
	pthread_t hilo[nEle];
	struct cuenta c[nEle];	
		
		
	//Reservamos memoria para el vector
	Vector=(int *)calloc(nEle,sizeof(int));
	if(Vector==NULL){
		printf("Error. No se pudo reservar memoria para el vector.\n");
	}
	
	//Generamos el vector
	for(i=0;i<nEle;i++){Vector[i]=rand()%10;}
	
	//Imprimimos el vector
	printf("( ");
	
	for (i=0;i<nEle;i++){
		printf("%d ",Vector[i]);
	}
	printf(")\n");
	
	//Reservamos memoria para la matriz
	Matriz=(int **)malloc(nEle*sizeof(int *));
	
	for(i=0;i<nEle;i++){
		Matriz[i]=(int *)malloc(nEle*sizeof(int));
	}
	
	//Generamos la matriz
	for(i=0;i<nEle;i++){
		for(j=0;j<nEle;j++){
			Matriz[i][j]=rand()%10;
		}
	}
	
	//Imprimimos la matriz
	for(i=0;i<nEle;i++){
		printf("|");
		for(j=0;j<nEle;j++){
			printf("%d",Matriz[i][j]);
		}
		printf("|\n");
	}
	
			
	//Creamos los hijos
	for (i=0;i<nEle;i++){
		c[i].indice=i;
		c[i].nEle=nEle;
		c[i].vector=Vector;
		c[i].matriz=Matriz;
		
		pthread_create(&hilo[i],NULL,(void *) hebra,(void *) &c[i]);
	}

	for(i=0;i<nEle;i++){
	
		pthread_join(hilo[i], (void **) &Vector_Resultado[i]);	
	}
	
	printf("El vector resultante es:\n ( ");
	for(i=0;i<nEle;i++){
	
		printf("%d ",Vector_Resultado[i]);
	}
	
		printf(")\n");	
	

return 0;
}

//funcion auxiliar

void *hebra (void * p){

	int i,j;
	struct cuenta * aux=(struct cuenta *) p;
	int res=0;
	printf("Soy el hilo %d.\n",aux->indice);

	for(i=0;i<aux->nEle;i++){
				
			res=res+ (aux->matriz[aux->indice][i] * aux->vector[i]);
	}
	


	pthread_exit( (void *)res);
}
