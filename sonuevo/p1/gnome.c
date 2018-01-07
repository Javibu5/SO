//PRÁCTICA 1. EJERCICIO 4
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

//Cabecera de la funciones
void hijo1 (char** argv);
void hijo2 (char** argv);

//Funcion principal
int main (int argc, char**argv){

	//Inicializamos las variables
	pid_t pid;
	int i,childpid,status;
	
		
	for(i=0;i<2;i++){
	pid=fork();
		switch(pid){

			case -1: 
	
		 	perror("fork error");
     	 	printf("errno value= %d\n", errno);

			exit(EXIT_FAILURE);

			case 0:

			if(i==0){
			hijo1 (argv);
			exit(EXIT_SUCCESS);
			}
			if(i==1){
			hijo2 (argv);
			exit(EXIT_SUCCESS);
			}
		}
	}
	
	
	childpid=wait(&status); 
	if(childpid>0){

		if (WIFEXITED(status)) {
          	printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
          	}
          	else if (WIFSIGNALED(status)) {
               	printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
               }
               else if (WIFSTOPPED(status)) {
               	printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
               } 


	
	}
return 0;
}

//Funciones

//Funcion hijo1: no devuelve nada. En este caso, sirve para que el primer proceso hijo abra la calculadora
void hijo1 (char** argv){
	
	execlp(argv[1],argv[1],NULL);
}
//Funcion hijo2: no devuelve nada. En este caso, sirve para que el segundo proceso hijo cree tanto ficheros de texto como se introduzcan por el Terminal a la hora de ejecutar el programa
void hijo2 (char** argv){

	execvp(argv[2],&argv[2]);
}
