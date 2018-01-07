#include <stdio.h>
#include <string.h>

struct parametros{//Esta estructura almacena todos los datos de la tabla de un proceso

	char nombre[10];
	int llegada;
	int ejecucion;
	int comienzo;
	int fin;
	int retorno;
	int espera;
};

#define NPROC 5

int main(){

	int i;
	struct parametros p[NPROC];//Creamos un vector para almacenar los datos de todos los procesos
	//Almacenamos los datos iniciales de cada proceso
	strcpy(p[0].nombre,"A");
	p[0].ejecucion=8;
	p[0].llegada=0;
	
	strcpy(p[1].nombre,"B");
	p[1].ejecucion=4;
	p[1].llegada=1;
	
	strcpy(p[2].nombre,"C");
	p[2].ejecucion=9;
	p[2].llegada=2;
	
	strcpy(p[3].nombre,"D");
	p[3].ejecucion=5;
	p[3].llegada=3;
	
	strcpy(p[4].nombre,"E");
	p[4].ejecucion=2;
	p[4].llegada=4;

	printf("Proceso\tT.Ejec\tT.Llegada\tT.Comienzo\tT.Fin\tT.Ret\tT.Espera\n");
	//Y procesamos esos datos para obtener los datos restantes de la tabla	
	for(i=0; i<NPROC; i++){
		
		if(i==0){
			p[i].comienzo=p[i].llegada;
		}	
		
		else{
				p[i].comienzo=p[i-1].fin;
		}
		
		p[i].fin= p[i].comienzo + p[i].ejecucion;
		
		p[i].retorno= p[i].fin - p[i].llegada;
		
		p[i].espera= p[i].comienzo - p[i].llegada;
		//Por ultimo se imprime por pantalla la tabla con todos los datos de cada proceso
		printf("%s\t%d\t%d\t\t%d\t\t%d\t%d\t%d\n", p[i].nombre,p[i].ejecucion,p[i].llegada,p[i].comienzo,p[i].fin,p[i].retorno,p[i].espera);
	}
	

return 0;
}
