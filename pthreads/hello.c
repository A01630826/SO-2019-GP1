#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	20

int saldo = 0;
pthread_mutex_t lockSaldo;

void *PrintHello(void *threadid) //void* apuntador a cualquier cosa
{
   long tid;
   int localsaldo;
   pthread_mutex_lock(&lockSaldo); //aqui ya se protege el saldo, estan corriendo en paralelo
   localsaldo=saldo;
    saldo=localsaldo+100;
    pthread_mutex_unlock(&lockSaldo);
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0;t<NUM_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t); //le pasa t como arg
     if (rc){ //cualquier cosa dif de 0, es error
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
    }
    for(t=0;t<NUM_THREADS;t++){
      pthread_join(threads[t], NULL);
    }
     printf("espero 2000 dlls tengo: %d\n", saldo);

   /* Last thing that main() should do */
   pthread_exit(NULL); //indica que se tienen todos los hilos y que se termine el proceso
}