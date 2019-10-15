#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //lib sleep
#include <time.h>

#define NUM_FILOS	5
pthread_mutex_t forks[NUM_FILOS];

void actions(){
    sleep(1+rand()%5); //dormir entre 1 y 5 sec
}

void * life(void *ptId){ //vida del filosofo
    long tid;
    tid = (long)ptId;
    srand(time(NULL)+ tid); //inicializar la semilla
    while(1){
            printf("voy a pensar un rato %ld\n",tid);
        actions();
            printf("Tengo hambre %ld\n",tid);
        if(tid % 2 == 0){ //con esto los dos van a competir
            pthread_mutex_lock(&forks[tid]); //agarrar el tenedor enfrente, pasandole la dirección para modif elmnto real
            printf("Tengo el tenedor derecho %ld\n",tid);
            pthread_mutex_lock(&forks[(tid+1)%NUM_FILOS]);//agarrar el de al lado
            printf("Tengo el tenedor izq %ld\n",tid);
            printf("A comer %ld\n",tid);
            actions();
            printf("Regresando tenedores %ld\n",tid);
            pthread_mutex_unlock(&forks[tid]);
            pthread_mutex_unlock(&forks[(tid+1)%NUM_FILOS]);

        }else{ //impar pero cambiar el orden
            pthread_mutex_lock(&forks[(tid+1)%NUM_FILOS]);
            printf("Tengo el tenedor izq %ld\n",tid);
            pthread_mutex_lock(&forks[tid]);
            printf("Tengo el tenedor der %ld\n",tid);
            printf("A comer %ld\n",tid);
            actions();
            printf("Regresando tenedores %ld\n",tid);
            pthread_mutex_unlock(&forks[tid]);
            pthread_mutex_unlock(&forks[(tid+1)%NUM_FILOS]);
        }
    }
}
//funcion main que cree los hilos
int main(){
 pthread_t threads[NUM_FILOS];
   int rc;
   long t;
   for(t=0;t<NUM_FILOS;t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, life, (void *)t); //le pasa t como arg
     if (rc){ //cualquier cosa dif de 0, es error
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
    }
    //esperar que todos los hilos terminen
    pthread_exit(NULL);
}