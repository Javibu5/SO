//gcc ejercicio7.c -lpthread
#include <unistd.h> 
#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
//variables globales
pthread_mutex_t mtx =PTHREAD_MUTEX_INITIALIZER;
int camiseta[5]={33,47,58,90,25};


void * cliente(){
	int modelo,cant,s;
	printf("Cliente\n");
	modelo=rand()%5;
	cant=rand()%10;
	printf("modelo %d  resta cant %d\n",modelo,cant);
	s=pthread_mutex_lock(&mtx); //lock the mutex
	if(s !=0){
		printf("Error en pthread_mutex_lock\n");
	}
	camiseta[modelo]-=cant;
	s=pthread_mutex_unlock(&mtx);//Unlock the mutex
	if(s !=0){
		printf("Error en mutex_unlock\n");
	}
	pthread_exit(NULL);    
}
void * proveedor(){
	int modelo,cant,s;
	printf("Poveedor\n");
	modelo=rand()%5;
	cant=rand()%10;
	printf("modelo %d  suma cant %d\n",modelo,cant);
	s=pthread_mutex_lock(&mtx); //lock the mutex
	if(s !=0){
		printf("Error en pthread_mutex_lock\n");
	}
	camiseta[modelo]+=cant;
	s=pthread_mutex_unlock(&mtx);//Unlock the mutex
	if(s !=0){
		printf("Error en mutex_unlock\n");
	}
    
	pthread_exit(NULL);
     
}
int main(int argc, char *argv[]){
	srand(time(NULL));
	int i,s,n,j; 
	if(argc==1){
		printf("Se esperaba %s <3>...\n",argv[0]);
		exit(EXIT_SUCCESS);
	}
	pthread_t thr[(atoi(argv[1]))+5],thrp[5];
	printf("-------camisetas=(");
	for(j=0;j<5;j++){
		printf("%d ",camiseta[j]);
	}
	printf(")-------\n");
	n=atoi(argv[1]);
    
	for (i=0;i<(n+5);i++){
		s=pthread_create (&thr[i], NULL, (void *)cliente,NULL); 
		if(s !=0){
			printf("Error en pthread_create\n");
		}
	} 
	for(i=0;i<5;i++){  
		s=pthread_create (&thrp[i], NULL, (void*)proveedor,NULL); 
		if(s !=0){
			printf("Error en pthread_create\n");
		}
	} 
	for(i=0;i<(n+5);i++){
		s=pthread_join(thr[i],NULL);
		if(s !=0){
			printf("Error en pthread_join\n");
		}
	}
	for(i=0;i<5;i++){  
        s=pthread_join(thrp[i],NULL);
            if(s !=0){
              printf("Error en pthread_join\n");
            }
	}
	printf("-------camisetas=(");
	for(j=0;j<5;j++){
		printf("%d ",camiseta[j]);
	}
	printf(")-------\n");
}
