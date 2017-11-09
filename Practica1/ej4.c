//ej4
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char  **argv)
{
	if(argc<4){
		printf("ERROR , faltan argumentos\n");
		exit(-1);
	}

pid_t pidprog1 , pidprog2;



	pidprog1 = fork();

	if(pidprog1==0){
		execvp(argv[1], &argv[1]);
		exit(0);

	}

	else return -1;

	pidprog2 = fork();

	if(pidprog2==0){

		  if ( execvp(argv[2], &argv[2]) < 0 ) //Exec devuelve -1 en caso de error 
            {
                perror("exec");
                printf("errno value= %d\n", errno); exit(EXIT_FAILURE);
            }
        }

	return 0;
}