#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int num = 0;
  int a=0;
  fprintf(stderr, "imprimendo los primos del 1 al 100 \n");

  while(1){
    int a=0;
    scanf("%d\n",&num);//noten que leo de stdout
    if(num == -1){
      break;
    }
    for(int i=1; i<100; i++){
        if(num % i == 0){
            a++;
        }
    }
    if(a==2){
        fprintf(stderr,"%d\n",num);
    }

  }
  fprintf(stderr, "completado\n");
}