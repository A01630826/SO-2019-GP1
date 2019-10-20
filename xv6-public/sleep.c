#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int i;

  if(argc < 2){
    printf(2, "sleep miliseconds");
    exit();
  }
  for(i=1; i<argc; i++){
    if(atoi(argv[i])>0)
        sleep(atoi(argv[i]));
    else
        printf(2, "indique tiempo");
  }
  exit();

}
