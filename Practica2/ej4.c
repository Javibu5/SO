//ej 4


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>







void * Suma(char nom[15]){

int *x = (int *)malloc(sizeof(int));

FILE * f = fopen( , "r");
char a;
a = fgetc(f);
	while(a != EOF ){
			if(a == '\n'){
				fi.i++;
			}
		a = fgetc(f);
	}
	printf("se hafg\n");
	fclose(f);
	*x = fi.i;
	pthread_exit(x);
}






int main(int argc, char **argv)
{


	if(argc == 1  ){
		printf("Argumentos invalidos\n");
		exit(-1);
	}


	pthread_t thd[argc];
	int * suma;
	int x = 0;
	char nombre[15];

	
	for(int i = 1 ; i < argc ; i++){
		
		strcpy(nombre , argv[i]);
		pthread_create (&thd[i], NULL, (void *) Suma, &nombre);

	}


	for(int j = 0 ; j<argc ; j++){
		printf("sdf\n");
		pthread_join(thd[j], (void **) &suma);
		printf("El hilo %d ha devuelto el valor %d\n",j, *suma);
		x = x + *suma;


	}

	printf("%d\n", x);
	 pthread_exit(NULL);



	return 0;
}