#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int forever = 1;

void signalHandler(int sgn){
    printf("received signal: %d\n", sgn);
    forever = 0;
}

int main (){
    int pid;
    pid = fork();
    if (pid == 0){
        //soy el hijo
        signal(10, signalHandler);
        //codigo que quiero que haga el hijo
        for(;;){}

    }else{
        printf("soy el proceso padre y mi hijo es: %d\n", pid);
        kill(pid, 10);
        //codigo del padre
        for(;;){}
    }

}