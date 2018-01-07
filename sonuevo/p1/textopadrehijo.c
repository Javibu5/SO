//PRÁCTICA 1. EJERCICIO 5
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(int argc, char ** argv){

	if(argc!=2){
	
	printf("error de sintaxis.Falta un argumento: ./programa fichero.txt\n");
	exit(-1);
	}
	

	//Se inicializan las variables
	pid_t pid;
	int i,childpid,status;
	FILE * f;

	pid=fork();

	for (i=0;i<3;i++){
	
	if(pid==-1){
	perror("fork error");
	printf("errno value= %d\n", errno);
	exit(EXIT_FAILURE);
	}
	
	
	if ((f=fopen(argv[1],"a"))==NULL) {
	printf("Error: No se pudo crear el fichero %s.\n","fich_datos.txt");
	exit(-1);
	}
	//Padre: escribe en el fichero de texto abierto una linea de '-'
	if(pid!=0){
	fprintf(f,"------\n");
	sleep(1);
	}
	//Hijo: escribe en el gichero de texto abierto una linea de '+'	
	if(pid==0){
	fprintf(f,"++++++\n");
	sleep(1);
	}
}	
	fclose(f);//Una vez finalize el programa se comprueba que el fichero de testo abierto/creado se ha editado correctamente
	if (pid==0){
	exit(EXIT_SUCCESS);}
	
	sleep(3);
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
return 0;}
