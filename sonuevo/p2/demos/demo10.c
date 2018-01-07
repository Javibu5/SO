#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

int thread_finished = 0;

void* start_function(void* value) 
{
    
    int *y = (int *) malloc(sizeof(int));
    *y = 10;
    printf("%s is now entering the thread function.\n", (char*)value); 
    sleep(4);
    thread_finished =1;
    printf("%s is now leaving the thread function.\n", (char*)value); 
    pthread_exit((void *)y);
}

int main() 
{
    int res,err,aux=7; 
    pthread_attr_t attr; 
    pthread_t thread1; 
    int *i;
    
    i = &aux;
    res = pthread_attr_init(&attr); 
    if (res != 0) 
    {
        perror("Attribute init failed");
        exit(EXIT_FAILURE); 
    }
    
  /*  res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 
    if (res != 0) 
    {
        perror("Setting detached state failed");
        exit(EXIT_FAILURE); 
    }  */
    
    res = pthread_create(&thread1, &attr, start_function, (void*) "Thread1"); 
    if (res != 0) 
    {
        perror("Creation of thread failed");
        exit(EXIT_FAILURE); 
    }
    
    while(!thread_finished) {
        printf("Waiting for thread1 to finish.\n"); 
        sleep(1);
    }
    
    pthread_join(thread1, (void**)&i); 
    printf("Valor devuelto:%d\n",*(int*)i);
    printf("Child thread finished.\n");
    pthread_attr_destroy(&attr); 
}