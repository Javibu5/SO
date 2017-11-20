//ej5.c

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>



void * Calculo(int matrizFuncion[2][3]){
	
	int *x = (int *)malloc(sizeof(int));
	
	int multiplicacion;
	for (int i = 0; i < ; ++i)
	{
		*x =  matrizFuncion[0]
	}
	

}

int main()
{
	int m[3][3]= {0 , 1 , 2} , {3 , 4 , 1} , {5 , 1 , 2};
	int v[3] = { 2 , 0 , 1};
	int maux[2][3];


	
	pthread_t thd[3];

	for(int i = 0; i < 3 ; i++){
		for (int j = 0; j < 3 ; ++j)
		{
			maux[0][j] = m[i][j];
			maux[1][j] = v[i];
		}
		pthread_create (&thd[i], NULL, (void *) Calculo, &maux);
	}



	return 0;
}