#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **lector() {
  /*TODO: Eventualmente, el fichero de entrada se seleccionará desde la
   * terminal, ya haré el scanf*/
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
  if (close(fd) != 0) {
    printf("El fichero se ha cerrado con un error \n");
    exit(1);
  }

  char **salida = malloc(strlen(buf + 1) * sizeof(char *));
  if (salida == NULL) {
    printf("Error al reservar memoria para tokens\n");
    exit(1);
  }

  int i = 0;
  int j = 0;
  int k = 0;
  int s = 0;
  int cb = 0;
  char *aux = malloc(2 * (size) * sizeof(char));

  while (buf[i] != '\0') {
    /*TODO: si llega al final del fichero, o el siguiente es el final,
     * básicamente, mete todo como una palabra, y tira palante;
     * -> Hay que comprobar en estados.c si lo gestiono o no.*/
    if (s || buf[i] == '"') {
      if (buf[i] == '"' && i != 0 && buf[i - 1] != '\\' && s == 1) {
        s = 0;
      } else if (buf[i + 2] == '\0') {
        s = 0;
        aux[k++] = '"';
        aux[k++] = 'N';
        aux[k++] = '\0';

      } else {
        s = 1;
      }
      aux[k++] = buf[i++];

    } else if (cb || (buf[i] == '/' && buf[i + 1] == '*')) {
      if (buf[i] == '*' && buf[i + 1] == '/') {
        cb = 0;
      } else if (buf[i + 1] == '\0' || buf[i + 2] == '\0') {
        aux[k++] = '*';
        aux[k++] = '/';
        aux[k++] = 'N';
        aux[k++] = '\0';
        cb = 0;
      } else {
        cb = 1;
      }
      aux[k++] = buf[i++];
      if (!cb) {
        aux[k++] = buf[i++];
      }

    } else if (buf[i] == '\t') {
      if (i != 0 && buf[i - 1] == '\t') {
        i++;
      } else {
        aux[k] = '\0';
        salida[j] = malloc(strlen(aux) + 1 * sizeof(char));
        memcpy(salida[j++], aux, strlen(aux) + 1);
        k = 0;
        i++;
      }
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
      if (k > 0) {
        aux[k] = '\0';
        salida[j] = malloc((k + 1) * sizeof(char));
        memcpy(salida[j++], aux, k + 1);
        k = 0;
      }
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
  /*TODO: hay que gestionar cuando no se cierra, para mandar un error a start.
   */
  salida = realloc(salida, (j + 1) * sizeof(char *));
  salida[j] = NULL;
  if (salida == NULL) {
    printf("Error al redimensionar memoria para tokens\n");
    exit(1);
  }

  return salida;
}
