//PRÁCTICA 1. EJERCICIO 2
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>
//Este ejercicio es pracicamente igual al ejercicio 1 solo que se comprueba con ayuda de otro terminal(escribimos ps -a) como el proceso queda en estado zombie(<defunct>) hasta que el padre recoge al hijo
int main (void){
	//Incializamos las variables
	pid_t pid;
	int childpid;
	int status;
	
	pid=fork();

       if(pid==0){
            printf("Proceso hijo %d; padre = %d\n", getpid(), getppid()); 
           exit(EXIT_SUCCESS); //return 0; 
       }
       else{
       printf("Proceso %d; padre = %d\n", getpid(), getppid());
       sleep(20);
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
         
            exit(EXIT_SUCCESS); //return 0;
      }
      

}
