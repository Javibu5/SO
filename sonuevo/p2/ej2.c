#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//estructura param
struct param{

	long num1;
	long num2;
	long suma;
};

//Cabecera funcion hilos

void * devuelve_suma (void *p);

int main() {
	int N,i;
	
	srand(time(NULL));
	
	printf("Introduce el numero de hebras que quiere crear:\n");
	scanf("%d",&N);
	
	struct param suma[N];
	long suma_Final=0;
	long * valor;
	pthread_t thd[N];//Array de hebras
	
	for (i=0;i<N;i++){
		pthread_create(&thd[i],NULL,(void *)devuelve_suma,(void *) &suma[i]);
	}

	for(i=0;i<N;i++){
		pthread_join(thd[i], (void **) &valor);
		printf("El hilo %d devuelve la suma: %ld\n",i,*valor);
		suma_Final= suma_Final + *valor;
	}
	
	printf("\n");	
	printf("La suma final de todas la sumas de los números generados aleatoriamente por los hilos es:%ld\n",suma_Final);
	
return 0;
}

//Funciones

void * devuelve_suma (void * p){
	
	struct param * aux;
	aux= (struct param *) p;
	long *valor;
	if ( (valor= (long *)calloc(1,sizeof(long)) ) == NULL){
		printf("\nError en reserva de memoria\n");	
		exit(-1);
	}  
	
	
	aux->num1=rand()%10;
	aux->num2=rand()%10;
	
	aux->suma= aux->num1 + aux->num2;
	*valor=aux->suma;
	
	printf("mi suma es %ld + %ld = %ld.\n",aux->num1,aux->num2,*valor);
	pthread_exit(valor);
}
