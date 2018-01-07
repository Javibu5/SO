//PRÁCTICA 1. EJERCICIO 7
#include<sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 


//Definimos la clave de acceso de la memoria compartida

#define Clave (key_t) 145

int main(){
	
	pid_t pid;
	int Id_Memoria;
	int * Memoria=NULL;
	int N,i,j;
	int status,childpid;
	

	//Introduce el numero de procesos a crear
	printf("Introduce el número de hijos a crear:\n");
	scanf("%d",&N);	
	
	
	if( (Id_Memoria = shmget (Clave, sizeof(int)*100, 0777 | IPC_CREAT)) ==-1){		
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}
	
	Memoria = (int*)shmat (Id_Memoria, (char*)0,0);
	
	//bucle que genera hijos	

	Memoria[0]=0;//se inicializa a cero el contador

	for(i=0;i<N;i++){
	pid=fork();

		switch(pid){

			case -1: //Error

				perror("fork error");
				printf("errno value= %d\n", errno); exit(EXIT_FAILURE);
            
        
			case 0: //Hijos

				for(j=0;j<100;j++){
					Memoria[0]++;
				}
				exit(0);
				exit(EXIT_SUCCESS);
	               
			default: //Padre
				printf("Proceso:%d, Padre:%d\n", getpid(), getppid());
				childpid=wait(&status); 
        if(childpid>0)
            {
                if (WIFEXITED(status)) {
                    printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
                } else if (WIFSTOPPED(status)) {
                    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
                } 
            }
         
        	}
    	}
    	printf("%d\n",Memoria[0]);//Da N*100
    	
    	/* Si se pusiese un numero muy grande y se ejecutase varias veces en alguna de ellas
    	 saldria un numero ligeramente menor al esperado ya que podría darse el caso de que
    	 dos hijos accediesen a la vez a la variable a incrementarla y entonces solo uno
    	 de ellos lo haría y el otro no, creando ese error */
    	
    	shmdt ((char *)Memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
    	
    	return 0;
    	
    	}









