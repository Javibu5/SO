//gcc ejercicio10.c -lpthread
#include <unistd.h> 
#include <pthread.h>
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <semaphore.h>  //para los semaforo
#define TAM 5
#define MAX_ITEMS 10

int buffer[TAM];
int contador=0;
sem_t s1,s2; 
void *productor(void* aux){
	int s,i,num_items=0,pos=0;
	while(num_items<=MAX_ITEMS){
	usleep(rand()%100000);
	sem_wait(&s1);                //sem_wait
	sem_post(&s2);
	if(contador!=TAM){
		buffer[pos]=rand()%10;
		printf("He producido %d en la posicion %d del buffer \n",buffer[pos],pos);
		pos=(pos+1)%TAM;
		contador++;
		num_items++;
	}
	sem_post(&s1);
	}
  
	pthread_exit(NULL);
}

void consumidor(){
	int s,i,num_items=0,pos=0;
	while(num_items<=MAX_ITEMS){
	usleep(rand()%500000);
       
	sem_wait(&s2);
	if(contador!=0){
		printf("He consumido %d en la posicion %d del buffer\n",buffer[pos],pos);
		pos=(pos+1)%TAM;
		contador--;
		num_items++;
	}
	sem_post(&s2);
	}
	pthread_exit(NULL);
   
}
void main(){
	int s,i;
	srand(time(NULL));
	pthread_t thr1,thr2;
	sem_init(&s2, 0, 0); //Semáforo inicializado a 0 
	sem_init(&s1, 0, 1); //Semáforo inicializado a 1 
	s=pthread_create (&thr1, NULL, (void *)productor,NULL); 
	if(s !=0){
		printf("Error en pthread_create\n");
	}
	s=pthread_create (&thr2, NULL, (void *)consumidor,NULL); 
	if(s !=0){
		printf("Error en pthread_create\n");
	}
	s=pthread_join(thr1,NULL);
	if(s !=0){
		printf("Error en pthread_join\n");
	}
	s=pthread_join(thr2,NULL);
	if(s !=0){
		printf("Error en pthread_join\n");
	}  
}
