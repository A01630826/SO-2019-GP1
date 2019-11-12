#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){

        char *file1 = argv[1];      //archivo viejo
        char *file2 = argv[2];      //archivo nuevo

        char *pwd = getcwd(NULL,0);
        
        char oldpath[strlen(file1) + strlen(pwd) + 2];
        char path[strlen(file2) + strlen(pwd) + 2];

        sprintf(oldpath,"%s/%s", pwd,file1);
        sprintf(path,"%s/%s",pwd,file2);

        link(oldpath, path);
        unlink(oldpath);
}