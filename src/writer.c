#include "tokens.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int writer(token **tokens) {
  int fd = creat("Salida.txt", 0644);
  if (fd == -1) {
    printf("Error al crear el archivo\n");
    return 1;
  }

  int i = 0;
  int final = 0;
  while (final == 0) {
    if (strcmp(tokens[i]->id_pal, "EOF") == 0)
      final = 1;
    char *buf = malloc(34 * sizeof(char));
    if (!buf) {
      printf("Error al reservar memoria\n");
      close(fd);
      return 1;
    }

    char *aux1 = tokens[i]->id_pal;
    char *aux2 = tokens[i]->atribute;

    buf[0] = '<';

    int j = 1;
    while (aux1[j - 1] != '\0') {
      buf[j] = aux1[j - 1];
      j++;
    }
    buf[j] = ',';
    j++;
    buf[j] = ' ';
    j++;

    int k = 0;
    while (aux2[k] != '\0') {
      buf[j + k] = aux2[k];
      k++;
    }
    j += k;

    buf[j] = '>';
    j++;
    buf[j] = '\n';
    j++;

    if (write(fd, buf, j) == -1) {
      printf("Error al escribir en el archivo\n");
      free(buf);
      close(fd);
      return 1;
    }

    free(buf);
    i++;
  }
  return 0;
}
