#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **lector() {

  int fd = open("TokensEntrada", O_RDONLY);
  if (fd == -1) {
    printf("Error al abrir el fichero\n");

    exit(1);
  }

  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char *buf = malloc(size + 1);
  read(fd, buf, size);
  buf[size] = '\0';

  char **salida = malloc(strlen(buf) * sizeof(char *));
  if (salida == NULL) {
    printf("Error al reservar memoria para tokens\n");
    exit(1);
  }

  int i = 0;
  int j = 0;
  int k = 0;
  char *aux = malloc(256 * sizeof(char));
  int s = 0;
  int cb = 0;

  while (buf[i] != '\0') {
    if (s || buf[i] == '"') {
      if (buf[i] == '"' && s == 1) {
        s = 0;
      } else {
        s = 1;
      }
      aux[k++] = buf[i++];
    } else if (cb || (buf[i] == '/' && buf[i + 1] == '*')) {
      if (buf[i] == '*' && buf[i + 1] == '/') {
        cb = 0;
      } else {
        cb = 1;
      }
      aux[k++] = buf[i++];
      if (!cb) {
        aux[k++] = buf[i++];
      }

    } else if (buf[i] == '\t') {
      i++;
    } else if (buf[i] == ' ') {
      if (i != 0 && buf[i - 1] == ' ') {
        i++;
      } else {
        aux[k] = '\0';
        salida[j] = malloc(strlen(aux) + 1 * sizeof(char));
        memcpy(salida[j++], aux, strlen(aux) + 1);
        k = 0;
        i++;
      }
    } else if (buf[i] == '\n') {
      aux[k] = '\0';
      salida[j] = malloc(strlen(aux) + 1 * sizeof(char));
      memcpy(salida[j++], aux, strlen(aux) + 1);
      k = 0;
      salida[j] = malloc(2 * sizeof(char));
      salida[j][0] = '\n';
      salida[j++][1] = '\0';
      i++;
    } else {
      aux[k++] = buf[i++];
    }
  }

  free(aux);
  free(buf);
  if (close(fd) != 0) {
    printf("El fichero se ha cerrado con un error \n");
    exit(1);
  }

  salida[j] = NULL;

  salida = realloc(salida, (j + 1) * sizeof(char *));
  if (salida == NULL) {
    printf("Error al redimensionar memoria para tokens\n");
    exit(1);
  }

  return salida;
}
