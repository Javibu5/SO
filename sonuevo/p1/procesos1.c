//PRÁCTICA 1. EJERCICIO 1 a).
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(){
	//Inicializamos variables
	pid_t pid;
	int childpid;
	int i,N;
	int status;
	//Introducimos por pantalla el números de hijos que queremos crear
	printf("Introduzca el número de procesos hijo que quiere crear:\n");
	scanf("%d",&N);
	
	//Hacemos un bucle iterativo que cree los procesos hijo y tras escribir en pantalla terminen y el padre los espere y compruebe que han terminado bien 
	for(i=0;i<N;i++){
	pid=fork();
	
	
        if (pid==0){//procesos hijos	
        	printf("Proceso hijo %d: %d; padre = %d, \n",i, getpid(), getppid()); 
                exit(EXIT_SUCCESS);
        	}
        	
        	//proceso padre
	
	printf("Proceso %d; padre = %d\n", getpid(), getppid());
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
	
 
	

return 0;
}
