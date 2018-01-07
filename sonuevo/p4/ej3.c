#include <stdio.h>
#include <string.h>

struct parametros{//Esta estructura almacena todos los datos de la tabla de un proceso
	char nombre[10];
	int ejecucion;
	int llegada;
	int comienzo;
	int fin;
	int retorno;
	int espera;
	int restante; //mide el tiempo restante tras cada ejecución

};

#define NPROC 5

int main(){

	int i,j,k;
	int t=0; //t=tiempo total consumido
	i=NPROC;
	
	struct parametros p[NPROC];//Creamos un vector para almacenar los datos de todos los procesos

	//Almacenamos los datos iniciales de cada proceso
	strcpy(p[0].nombre,"A");
	p[0].ejecucion=8;
	p[0].llegada=0;
	p[0].restante=p[0].ejecucion;
	
	strcpy(p[1].nombre,"B");
	p[1].ejecucion=4;
	p[1].llegada=1;
	p[1].restante=p[1].ejecucion;
	
	strcpy(p[2].nombre,"C");
	p[2].ejecucion=9;
	p[2].llegada=2;
	p[2].restante=p[2].ejecucion;
	
	strcpy(p[3].nombre,"D");
	p[3].ejecucion=5;
	p[3].llegada=3;
	p[3].restante=p[3].ejecucion;
	
	strcpy(p[4].nombre,"E");
	p[4].ejecucion=2;
	p[4].llegada=4;
	p[4].restante=p[4].ejecucion;
	
	while(i>0){
		printf("\nProceso\tT.Ejec\tT.Comienzo\tT.Fin\tT.Restante\n");
		
		for(j=0; j<NPROC; j++){
			
			if(p[j].restante != 0){ //si el t. restante es 0 ese proceso ya ha acabado
				
				p[j].comienzo=t; //En t almacenamos el t. tot. consumido, el t. comienzo del proceso siguiente será t
				
				for(k=0; k<3 && p[j].restante>0; k++){//Al t. restante se le resta el t. consumido durante el ciclo, y se le añade al t. total "t"
					t++;										
					p[j].restante--;
				}
				
				if(p[j].restante==0){
					i--;
				}
				
				p[j].fin=t;
				
				printf("%s\t%d\t%d\t\t%d\t%d\n", p[j].nombre,p[j].ejecucion,p[j].comienzo,p[j].fin, p[j].restante);
			}
		}
	}
	
	printf("\nProceso\tT.Retorno\tT.Espera\n");
	
	for(i=0; i<NPROC; i++){//Y procesamos e imprimimos esos datos para obtener los datos restantes de la tabla
		p[i].retorno=p[i].fin-p[i].llegada;
		p[i].espera=p[i].retorno-p[i].ejecucion;
		printf("%s\t%d\t\t%d\n", p[i].nombre,p[i].retorno, p[i].espera);
	}
	
	return 0;
}
