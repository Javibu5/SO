//ej3

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>




typedef struct {
    int *ar;
    long n;
} subarray_t;


// Thread que incrementa n componentes de un array
void *incrementer (subarray_t * arg) {

   int *suma = (int *)malloc(sizeof(int));
   *suma = 0;
    int i;
        for (i=0; i < arg->n; i++) {
        *suma = *suma + arg->ar[i];
    } 

    printf("Soy el hilo y mi suma es %d\n" , * suma );
    pthread_exit(suma);
}

// programa principal que reparte entre los threads el trabajo
// de incrementar los componentes de un array
	

int main(int argc, char **argv)
{
	if(argc != 2 ){
		printf("Argumentos invalidos\n");
		exit(-1);
	}

    srand(time(NULL));
	int const n = atoi(argv[1]);
	int *valor_devuelto;
    int ar [10]; 
    long suma=0,i;
    int neh = 10/n;

    pthread_t th[n];
    subarray_t sv[10/n];
    
    // inicializa los elementos a un numero aletorio
    
    for (i=0; i<9; i++){
        ar[i] = rand() % 10;       
        printf("%d\n", ar[i] ); 
    }

    //repartimos las tareas

    /*sv[0].ar = &ar[0];

    for(i=1 ; i < 10/n ; i++){


	    if(10%i == 0){

	    	sv[i].n = 10/n;
	    }
	    else sv[i].n = 10/n + 1;
		
		sv[i].ar = &ar[i*(10/n)];	

	}*/

    for (i=0 ; i<n ; i++){

       sv[i].ar = &ar[i*neh];
        sv[i].n = neh;
        if(10%n != 0 && i == (n - 1)){
            
    		pthread_create(&th[i], NULL,(void*)incrementer, &sv[i]);
        }
    		
    }
    
  
    
  for (int j = 0; j < n; ++j)
	{
		
		pthread_join(th[j], (void **) &valor_devuelto);
        printf("El hilo %d ha devuelto el valor %d\n",j, *valor_devuelto);
        suma = suma + *valor_devuelto;

     
    }
    printf("%d\n", suma );
	
	return 0;
}