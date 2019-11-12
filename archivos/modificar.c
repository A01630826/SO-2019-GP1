#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void comparar(int fd2, char *wordx) {
  write(fd2, wordx, strlen(wordx));
  write(fd2, " ", 1); // solo se quiere escribir un caracter en blanco
}
int main(int argc, char **argv) {
  char *fileName = argv[1]; // nombre del archivo
  char word[100];           // buffer para ir guardando palabrar a leer
  char ca;                  // ir leyendo caracter por carac
  int i = 0;
  int fd = open(fileName, O_RDONLY); // un file
  int fd2 = open("tmp.txt", O_WRONLY | O_CREAT, 0666);

  while (read(fd, &ca, 1)) {
    if (ca != ' ') {
      word[i++] = ca;
    } else {
      word[i] = '\0';
      i = 0;
      if (!strcmp(word, argv[2])) { // si son iguales
        comparar(fd2, argv[3]);
      } else { // else escribir lo mismo
        comparar(fd2, word);
      }
    }
  } // regresará 0 cuando ya no tenga qué leer, lo cierra y termina
  word[i] = '\0';
  if (!strcmp(word, argv[2])) { // si son iguales
    comparar(fd2, argv[3]);
  } else { // else escribir lo mismo
    comparar(fd2, word);
  }

  close(fd);
  close(fd2);
  unlink(fileName);
  link("tmp.txt", fileName);
  unlink("tmp.txt");
  return 0;
}