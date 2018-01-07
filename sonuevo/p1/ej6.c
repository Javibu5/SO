//PRÁCTICA 1. EJERCICIO 6
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

//Se inicaliza la variable contador global
int a=0;

int main(){
	//Se inicalizan las variables
	pid_t pid;
	int childpid;
	int i,N;
	int status;
	
	//Se introducen por pantalla el número de procesos hijo a crear que intentan incrementar(sin exito) la variable global 'a'
	printf("Introduzca el número de procesos hijo que quiere crear:\n");
	scanf("%d",&N);
	
	for(i=0;i<N;i++){
	pid=fork();
	
	
        if (pid==0){//procesos hijos	
        	printf("Proceso hijo %d: %d; padre = %d, \n",i, getpid(), getppid()); 
                a++;
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
     //Al final del programa se comprueba efectivamente, que 'a' conserva su valor incial, 0.
	printf("a=%d\n",a);
 
	

return 0;
}
