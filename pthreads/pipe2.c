#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int primo = 0;
    int num = 0;

    scanf("%d\n",&primo);
    fprintf(stderr, "%d\n", primo);

    while(num >= 0) {
        scanf("%d\n",&num); // //noten que leo de stdout

        if(num % primo != 0){
            printf("%d\n",num);
        }
    }
    printf("%d\n",num);
}