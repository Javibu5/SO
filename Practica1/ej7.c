#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> 

#define Clave (key_t) 234

int main()
{

	pid_t rf;
	int status , childpid;

	int Id_Memoria;
	int *memoria = NULL;

	Id_Memoria = shmget (Clave, sizeof(int)*2, 0777 | IPC_CREAT);
	if (Id_Memoria == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit (0);
	}




	for (int i = 0; i < 10 ; ++i)
	{
		rf = fork();

		if (rf == -1)
		{
			printf("Error en la creacion del hijo\n");
			printf("errno value= %d\n", errno); exit(EXIT_FAILURE);
		}

		else {
			memoria = (int *)shmat (Id_Memoria, (char *)0, 0);
				if (memoria == NULL)
				{
				printf("No consigo Memoria compartida");
				exit (0);
					}
			for (i=0; i<100; i++)
				{
					memoria[1] = memoria[1] + 1;
			
				}
		}
shmdt ((char *)memoria);
}

while((childpid=wait(&status))>0){
	printf(" mi pid es %d\n ",  getpid());
}


	printf("%d\n", memoria[1]);

	shmdt ((char *)memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);




	
	
	return 0;
}