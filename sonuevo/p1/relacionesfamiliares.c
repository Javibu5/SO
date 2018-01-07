//PRÁCTICA 1. EJERCICIO 3
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(){
	//Inicializamos variables
	pid_t pid;
	int status,childpid,suma=0;
	
	pid=fork();
	if(pid==0){//primer hijo
		suma=suma+getpid()%10;
		printf("Soy el primer hijo (pid=%d) y mi suma es: %d\n",getpid(),suma);
		exit(suma);
	}//cierra primer hijo
	
	sleep(5);//sleep primer hijo
	
	pid=fork();
	if(pid==0){//segundo hijo
		
		pid=fork();
		if(pid==0){//primer nieto
			suma=suma+getpid()%10;
			printf("Soy el primer nieto (pid=%d) y mi suma es: %d\n",getpid(),suma);
			exit(suma);
		}//cierra primer nieto
	
		sleep(5);//sleep primer nieto
		
		pid=fork();
		if(pid==0){//segundo nieto
			pid=fork();
			if (pid==0){//bisnieto
				suma=suma+getpid()%10;
				printf("Soy el bisnieto (pid=%d) y mi suma es: %d\n",getpid(),suma);
				exit(suma);
			}//cierra bisnieto
		
			sleep(5);//sleep bisnieto
		
			childpid=wait(&status);//el segundo nieto espera al bisnieto
			suma=(suma+getpid()%10)+WEXITSTATUS(status);//se guarda en la variable SUMA del segundo nieto su última cifra del pid y se le añade la SUMA del bisnieto
			printf("Soy el segundo nieto (pid=%d) y mi suma es: %d\n",getpid(),suma);
			exit(suma);
		}//cierra segundo nieto
		
		sleep(5);//sleep segundo nieto, AUNQUE NO HACE FALTA, ya que esto no se va a notar en la ejecución porque mientras hace este sleep esta haciendose los anteriores simultaneamente
		
		//Como cuando no hay mas hijos que esperar wait devuelve -1 y poner un valor en errno hacemos un bucle que mientras sea distinto de -1 espere y recoja a los hijos
		while(wait(&status)!=-1){
		suma=suma+WEXITSTATUS(status);
		}
		//luego se le suma su ultima cifra para obtener su suma
		suma=suma+getpid()%10;
		printf("Soy el segundo hijo (pid=%d) y mi suma es: %d\n",getpid(),suma);
		exit(suma);
		}//cerramos segundo hijo
		
		sleep(5);//sleep segundo hijo, AUNQUE NO HACE FALTA, ya que esto no se va a notar en la ejecución porque mientras hace este sleep esta haciendose los anteriores simultaneamente
		
	//a continuación se hace exactamente lo mismo pero con el padre y sus dos hijos
	while(wait(&status)!=-1){
	suma=suma+WEXITSTATUS(status);
	}
	
	suma=suma+getpid()%10;
	printf("Soy el padre (pid=%d) y mi suma es: %d\n",getpid(),suma);
	
	return 0;
}
