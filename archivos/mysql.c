#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s{
    char firstName[20];
    char lastName[20];
    int studentId;
    char semester;
} Student; //el alias

int writeStudent(int argc, char **argv){
    char *fileName = argv[1];
    int fd = open(fileName, O_WRONLY | O_CREAT, 0666);
   
    //crear 10 elementos tipo student y escribirlos en el archivo
    for(int i=0; i<10; i++){
        Student myStudent; //nombre del tipo de dato
        myStudent.studentId = (i+1)*10;
        myStudent.semester = (i+1);
        sprintf(myStudent.firstName, "Juanito_%d", i);
        sprintf(myStudent.lastName, "Perez_%d", i);
        write(fd, &myStudent, sizeof(myStudent));

    }
    close(fd);
    return 0;    
}
int readStudent(int argc, char**argv){
    char *fileName = argv[1];
    int fd = open(fileName, O_RDONLY);
    //ejemplo para lectura
    Student myStudent;
    while(read(fd, &myStudent, sizeof(myStudent))){
        printf("%s %s : %d: %d\n", myStudent.firstName, myStudent.lastName, myStudent.studentId, myStudent.semester);
    }
    close(fd);
    return 0;
}
int main(int argc, char **argv){
    char *fileName = argv[1];
    char *lastName = argv[2];
    char *newLastName = argv[3];
    int recordPos = -1;
    int i= -1;
    int fd = open(fileName, O_RDONLY);
    readStudent(argc, argv);
    Student myStudent;

    while(read(fd, &myStudent, sizeof(myStudent))){
        i++;
        if(!strcmp(myStudent.lastName, lastName)){
            recordPos = i; //variable para llevar la cuenta
            break;
        }
    }
    close(fd);
    if(recordPos != -1){ //si es diferente de -1 significa que lo encontré
        printf("El record existe en la posicion %d\n", recordPos);
        char lastNameBuf[sizeof(myStudent.lastName)];
        strncpy(lastNameBuf, newLastName, sizeof(myStudent.lastName));
        fd = open(fileName, O_WRONLY);
        lseek(fd, recordPos*sizeof(myStudent) + sizeof(myStudent.firstName), SEEK_SET); //se brinca la cantidad de record y luego el firstname
        write(fd, lastNameBuf, sizeof(myStudent.lastName));
        close(fd);
    }else{
        printf("el record no existe\n");
    }
    return 0;
}

/*
vimos como "mas o menos " se maneja un archivo binario.
La primera parte del codigo buscarlo y ver modo lectura, la segunda fue de modo escritura
lseek es una funcion que te permite moverte de un archivo la cant que quieras
strcopy copia una cadena en otra pero n cantidad de bytes. que si es más chica la rellena de 0s sino 
el compilador de c en los arreglos lo ubica en la direccion del primer elemento y de ahí empezará a escribir
el sizeof tiene que agarrar el bloque de memoria y contar los bytes

*/