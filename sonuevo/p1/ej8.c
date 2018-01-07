//PRÁCTICA 1. EJERCICIO 8

#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> //para wait()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>
#include <string.h> 
#include <sys/shm.h>

//Definimos la clave de acceso a la memoria compartida
#define Clave (key_t) 232

int main(){

	//Inicializamos las variables
	int i,childpid,status,pid,Id_Memoria,N=3;
	int * Memoria=NULL;
	
	
	//Reservamos una zona de memoria compartida
	if( (Id_Memoria=shmget( Clave , sizeof(int)*5 , 0777 | IPC_CREAT))==-1 ){
		printf("No consigo Id para memoria compartida\n");
		exit(-1);
	}	
	
	//Damos acceso a los procesos a la memoria compartida reservada anteriormente
	if ( (Memoria = (int *)shmat ( Id_Memoria , (char *)0 , 0 )) == NULL){
		printf("No consigo Memoria compartida");
		exit(-1);
	}
	
	/*Inicializamos el contador y el token ring o testigo que es un puntero que apunta a
	la posicion del vector con el que se asocia cada hijo (hacia que proceso hijo apunta)*/
	
	Memoria[0]=0;
	Memoria[1]=2;	
	
	/*Hacemos un bucle iterativo en el que los procesos hijos se vayan pasando el token ring
	 (testigo) para tener acceso a la memoria y poder incrementar en 1 el contador,cuando
	 el proceso hijo que tenga el testigo haya accedido y realizado el incremento, sale de
	 la memoria y pasa el testigo al siguiente hijo asi ssucesivamente hasta que cada hijo 
	 haya incrementado 100 veces el contador que esta en la zona de memoria compartida.*/
	for(i = 0; i < N; i++){
		pid = fork();
		
		if(pid == 0){
			printf("Pid: %d, padre: %d\n", getpid(), getppid());
			
			for (i=0; i<100; ){
				
				if(Memoria[Memoria[1]]==getpid()){		
					
					Memoria[0]++;
					Memoria[1] = (Memoria[1]+2)%N + 2;
					i++;
				}
			}					
			exit(0);
		}
		
		else if(pid > 0){
			Memoria[2+i]=pid;
		}
		else{
			perror("fork error");
			printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno)); 
			exit(EXIT_FAILURE);
		}	
	}

	for(i = 0; i < 3; i++){
		pid = wait(&status);
		printf("child %d exited, status=%d\n",pid, WEXITSTATUS(status));
	}
	
	//Imprimimos el valor de la variable Contador que deberia dar 300(N=3 * 100 iteraciones/hijo).
	printf("CONTADOR = %d\n", *Memoria);

	//Liberamos la memoria
	shmdt ((char *)Memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
	
	return 0;
}
