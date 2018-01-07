//gcc ejercicio8.c -lpthread
#include <unistd.h> 
#include <pthread.h>
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#define TAM 5
#define MAX_ITEMS 10

int buffer[TAM];
int contador=0;
pthread_mutex_t mtx =PTHREAD_MUTEX_INITIALIZER;
void *productor(void* aux){
	int s,i,num_items=0,pos=0;
	while(num_items<=MAX_ITEMS){
	usleep(rand()%100000);
	s=pthread_mutex_lock(&mtx); //lock the mutex
	if(s !=0){
		printf("Error en pthread_mutex_lock\n");
	}
	if(contador!=TAM){
		buffer[pos]=rand()%10;
		printf("He producido %d en la posicion %d del buffer \n",buffer[pos],pos);
		pos=(pos+1)%TAM;
		contador++;
		num_items++;
	}
	s=pthread_mutex_unlock(&mtx);//Unlock the mutex
	if(s !=0){
		printf("Error en mutex_unlock\n");
	}
	}
	pthread_exit(NULL);  
}

void consumidor(){
	int s,i,num_items=0,pos=0;
	while(num_items<=MAX_ITEMS){
	usleep(rand()%500000);
	s=pthread_mutex_lock(&mtx); //lock the mutex
	if(s !=0){
		printf("Error en pthread_mutex_lock\n");
	}
	if(contador!=0){
		printf("He consumido %d en la posicion %d del buffer\n",buffer[pos],pos);
		pos=(pos+1)%TAM;
		contador--;
		num_items++;
	}
	s=pthread_mutex_unlock(&mtx);//Unlock the mutex
	if(s !=0){
		printf("Error en mutex_unlock\n");
	}
	}
	pthread_exit(NULL);
   
}
void main(){
	int s,i;
	srand(time(NULL));
	pthread_t thr1,thr2;
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
