// n/h (n/h +1) n%h h-(n%h)
//  <*      >     >      <*
// x suma  ysuma      y hijo x hijos


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
//Estructura suma_Vector

struct suma_Vector{
	int indice;
	int nEle;
	int * vector;
	int numhebra;
};	

//Cabeceras

void * hebra (void * v);

//Funcion Principal
int main(int argc,char **argv){


	if (argc!=2){
		
		printf("ERROR en la sintaxis. ""/.miprograma numhilos""\n");
		exit(-1);
	}
	int * Vector; 
	int i,numEle,hilos1,num1,hilos2,num2;
	int sumaTotal=0; 
	long sumaHilo=0;
	
	int numHilos= atoi(argv[1]);
	srand(time(NULL));
	struct suma_Vector sum[numHilos];
	pthread_t hilo[numHilos];
	
	printf("El numero de hilos es: %d.\n",numHilos);	
	
	//Creacion del vector
	printf("Introduce el numero de elementos de un vector:\n");
	scanf("%d",&numEle);
	Vector=(int *)calloc(numEle,sizeof(int));
	if(Vector==NULL){
		printf("Error. No pudo asignarse memoria al vector.\n");
		exit(-1);
	}
	
	//Rellenamos el vector
	for(i=0;i<numEle;i++){
		Vector[i]=rand()%10;
	}
	
	//Imprimimos el vector
	printf("El vector generado es: ( ");
	for(i=0;i<numEle;i++){
		printf("%d ",Vector[i]);
	}
	printf(")\n");
	
	//Asignamos mediante variables con un algoritmo el numero de elementos que le toca a cada hilo sumar
	
	num1= numEle/numHilos;
	hilos1= numHilos - (numEle%numHilos);
	
	num2= (numEle/numHilos) + 1;
	hilos2= numEle%numHilos;
	
	//Asignamos a cada hilo cuantos elementos le tocan y lo creamos
	for(i=0;i<numHilos;i++){
	
		sum[i].numhebra=i;
		if(i<hilos1){
			sum[i].nEle=num1;
		}
	
		else{
			sum[i].nEle=num2;
		}
		
		sum[0].indice=0;
		if(i!=0){sum[i].indice= sum[i-1].indice + sum[i-1].nEle;}
		
		sum[i].vector=Vector;
		
		pthread_create(&hilo[i],NULL, (void *) hebra, (void *) &sum[i]);	
	
	}
	
	for(i=0;i<numHilos;i++){
		
		pthread_join(hilo[i], (void **) &sumaHilo);
		
		sumaTotal=sumaTotal+ sumaHilo;
		
	}
	
	printf("Suma total:%d.\n",sumaTotal);

return 0;
}


//Funcion auxiliar

void * hebra (void * p){

	int i;
	long suma=0;
	struct suma_Vector *aux= (struct suma_Vector *) p;
	
		for ( i=0; i < aux->nEle ;i++){
	
			suma= suma + aux->vector[(aux->indice)+i];
		}
	printf("Soy el hilo %d y mi suma es:%ld.\n",aux->numhebra,suma);
	
	pthread_exit((void *)suma);
}
