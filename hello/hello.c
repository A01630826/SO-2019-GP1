#include <stdio.h>
#include "./libhello.h"

int main(int argc, char **argv){
    int i;
    for (i=1; i< argc; i++){
        printHello(argv[i]);
    }
    return 0;
}