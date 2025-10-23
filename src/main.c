#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd = open("TokensEntrada", O_RDONLY);
  int size;
  char *buf;
  if (fd == -1) {
    printf("Error al abrir el fichero");
    exit(1);
  }

  /*Aquí deberíamos implementar el lector directamente, hay que hacer un struct
   * que desarrolle las propiedades de los tokens (eventualmente xd ) */
  size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  read(fd, &buf, size);
  printf("%s", buf);

  if (close(fd) != 0) {
    printf("El fichero se ha cerrado con un error.");
    return -1;
  }
  return 0;
}
