//ejercicio1

#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h> 

int main()
{
	int n, i ;
	pid_t rf;
	int status , childpid;

	scanf("%d" , &n);


	for (i = 0; i < n; ++i)
	{

		rf=fork();
	 	switch(rf)
    {
        case -1:
            perror("fork error");
            printf("errno value= %d\n", errno); exit(EXIT_FAILURE); 
            //return (-1);
            
        case 0: /* proceso hijo */
			
            printf("Proceso hijo %d; padre = %d \n", getpid(), getppid()); 
            exit(EXIT_SUCCESS);
            
        default: /* padre */
            printf("Proceso %d; padre = %d,\n", getpid(), getppid());
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
	

}