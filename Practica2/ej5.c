//ej5.c

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>



void * Calculo(int * matrizFuncion[2][3]){
	
	int *x = (int *)malloc(sizeof(int));
	

	int multiplicacion;

	for (int i = 0; i < 3 ; ++i)
	{
		printf("%d\n", *matrizFuncion[0][i]);
		printf("%d\n", *matrizFuncion[1][i]);
		multiplicacion =  *matrizFuncion[0][i] * (*matrizFuncion[1][i]);
		*x =+ multiplicacion;
	}


	
	pthread_exit(x);

}

int main()
{
	int m[3][3]= {{0 , 1 , 2},{3 , 4 , 1},{5 , 1 , 2}};
	int v[3] = { 2 , 0 , 1};
	int maux[2][3];

	int * suma;
	int resultado = 0;
	int vector[3];


	
	pthread_t thd[3];

	for(int i = 0; i < 3 ; i++){
		
			
		for (int j = 0; j < 3 ; ++j)
		{
			maux[0][j] = m[i][j];
			maux[1][j] = v[j];
		
		}

		pthread_create (&thd[i], NULL, (void *) Calculo, &maux);
	}

	for(int j = 0 ; j<3 ; j++){
		pthread_join(thd[j], (void **) &suma);
		printf("El hilo %d ha devuelto el valor %d\n",j, *suma);
		vector[j] = *suma; 


	}
for (int k = 0; k < 3; ++k)
{
	printf("%d\n", vector[k]);
	
	
}

		return 0;
}