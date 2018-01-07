//gcc ejercicio9.c -lpthread
#include <unistd.h> 
#include <pthread.h>
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#define TAM 1024

struct copia{
   char nombre[25];
   int num;
};
//Variables globales
sem_t *lec;
sem_t esc;
char buffer[TAM];
char *linea;
int num_copias;
pthread_mutex_t mtx =PTHREAD_MUTEX_INITIALIZER;

void * LeerFichero(char * nombre){
    int s,i=0;
    FILE *f;
    f=fopen(nombre,"r");
    while(1){
    
       printf("Leer\n");
       sem_post(&esc);                          //sem_post
       s=pthread_mutex_lock(&mtx);              //lock the mutex 
       if(s !=0){
               printf("Error en mutex_lock\n");
            }
       linea=fgets(buffer,1024,f);
       printf("Linea <%s>\n",linea);
       s=pthread_mutex_unlock(&mtx);            //Unlock the mutex
       if(s !=0){
               printf("Error en mutex_unlock\n");
            }  
       for(i=0;i<num_copias;i++) sem_post(&lec[i]);
          printf("Buffer <%s>\n",buffer);
          
       if(linea!=NULL){
          sleep(1);
          sem_wait(&esc);
       }else{
          break;
       }
   }
   fclose(f);
   pthread_exit(NULL);
}

void *copia(struct copia *cop){
   int s;
   char cad[25];
   FILE* c;
   
   sprintf(cad,"%d",cop->num);
   strcat(cop->nombre,cad);
   
   c=fopen(cop->nombre,"w");
   while(1){
      printf("%s\n",cop->nombre);
      printf("Copiar\n");
      
      sem_wait(&lec[cop->num]);
      sem_wait(&esc);
      
      if(linea!=NULL){
      
         s=pthread_mutex_lock(&mtx); //lock the mutex
            if(s !=0){
               printf("Error en pthread_mutex_lock\n");
            }
         fprintf(c,buffer);  //............
         s=pthread_mutex_unlock(&mtx);//Unlock the mutex
            if(s !=0){
               printf("Error en mutex_unlock\n");
            }
         sem_post(&esc);
   
      }else{
         sem_post(&esc);
         
         break;
      }
   }
   fclose(c);
  
   pthread_exit(NULL);
}


int main(int argc, char *argv[]){
   int i,s,j,k;
   num_copias=atoi(argv[2]);
   lec=(sem_t*)malloc(sizeof(sem_t)*(atoi(argv[2])));
   struct copia cad[num_copias];
   if(argc==1){
       printf("Se esperaba %s <fichero> <3>...\n",argv[0]);
       exit(EXIT_SUCCESS);
    }
    
   pthread_t thr[atoi(argv[2])],thrLeer;
   
   for(j=0;j<atoi(argv[2]);j++){
      cad[j].num=j;
      strcpy(cad[j].nombre,argv[1]);
   }
   for(i=0;i<atoi(argv[2]);i++) sem_init(&lec[i],0,0);
   
   sem_init(&esc,0,0);
   
   s=pthread_create (&thrLeer, NULL, (void *)LeerFichero,argv[1]); 
   usleep(100);
      if(s !=0){
         printf("Error en pthread_create de LeerFichero\n");
      }
   for(i=0;i<atoi(argv[2]);i++){
       printf("%d\n",i);
      s=pthread_create (&thr[i], NULL, (void *)copia,&cad[i]); 
         if(s !=0){
            printf("Error en pthread_create de copia\n");
         }
   }
   
   s=pthread_join(thrLeer,NULL);
      if(s !=0){
         printf("Error en pthread_join\n");
      }
   for(i=0;i<atoi(argv[2]);i++){
      s=pthread_join(thr[i],NULL);
        if(s !=0){
           printf("Error en pthread_join\n");
        }    
   }
   pthread_mutex_destroy(&mtx);
   sem_destroy(&esc);
   for(k=0;k<atoi(argv[2]);k++) sem_destroy(&lec[k]);
}
