//ej3

#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h> 

void esperar(int seg , char * nombre);

int main(){
	int  pid;
	pid_t pidh1 , pidh2 , pidn1, pidn2 , pidb1;

	pidh1=fork();

	if(pidh1==0){
	  	
		esperar(0 , "hijo 1");
	}

	pidh2=fork();

	if(pidh2==0){
		 

		  pidn1=fork();

		  if(pidn1==0){
	  			
				esperar(0 , "nieto 1");	
			}
			
			pidn2=fork();

		  		if(pidn2==0){
	  				

						pidb1=fork();
		  					if(pidb1==0){
	  							
								esperar(1 , "bisnieto");
							}
					
				esperar(2 , "nieto 2");
				
			}

			esperar(3 , "hijo 2");
		}
		
		esperar (5 , "padre");
}


void esperar (int seg , char * nombre){
	int suma , childpid , status;
	sleep(seg);
	suma = getpid()%10;
	while((childpid=wait(&status))>0){
		if(WIFEXITED(status)>0) suma+=WEXITSTATUS(status);
	}

	printf("Soy %s , mi pid es %d y mi suma es %d\n", nombre , getpid() , suma);
	exit(suma);
}