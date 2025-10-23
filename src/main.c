#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  int fd = open("TokensEntrada", O_RDONLY);
  if (fd == -1) {
    printf("Error al abrir el fichero");
    exit(1);
  }

  /*Aquí deberíamos implementar el lector directamente, hay que hacer un struct
   * que desarrolle las propiedades de los tokens (eventualmente xd ) */
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char buf[size];
  read(fd, buf, size);

  /*Prueba a escribirlo en otro fichero*/
  int fd2 = creat("Salida.txt", 0777);
  write(fd2, buf, size);

  /* Sobre buf hay que aplicar strtok, para de esta manera dividir los tokens en
   * sus componentes <(lo que haya)>, strtok, básicamente nos permite crear
   * nuevos strings, se crean con un bucle simple, y luego analizar dichos
   * strings., también se puede arreglar comparando caracter a caractér,
   * probablemente nos de menos problemas */
  int i = 0;
  while (buf[i] != '\0') {
    /* Aquí se llamaría a otro método que almacene un puntero a string, cuyos
     * strings sean los tokens*/
    printf("%c", buf[i]);
    i++;
  }
  if (close(fd) != 0 || close(fd2) != 0) {
    printf("El fichero se ha cerrado con un error.");
    return -1;
  }

  return 0;
}
