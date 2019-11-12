#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){

        char *file = argv[1];      //archivo a borrar
        char *pwd = getcwd(NULL,0);
        
        char oldpath[strlen(file) + strlen(pwd) + 2];
        sprintf(oldpath,"%s/%s", pwd,file);
        unlink(oldpath);
}