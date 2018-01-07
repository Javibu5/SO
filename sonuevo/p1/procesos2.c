#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(){

	pid_t pid;
	int childpid;
	int i,N;
	int status;
	printf("Introduzca el número de procesos hijo que quiere crear:\n");
	scanf("%d",&N);
	printf("Proceso padre absoluto %d; padre = %d\n", getpid(), getppid());
	
	
	for (i=0;i<N;i++){
	pid=fork();
	
        if (pid==0){//procesos hijos	
               	printf("Proceso hijo %d: %d; padre = %d, \n",i, getpid(), getppid()); 
        	
                
        	}
        	
        	//proceso padre
	
	
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
           
            exit(EXIT_SUCCESS);
            }
         
        }
	
 
	

return 0;
}
