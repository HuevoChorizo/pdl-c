#include "tokens.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int writer(token **tokens) {
  int fd = creat("Salida.txt", 0777);
  if (fd == -1) {
    printf("Tonoto no sabe ejcribir archivos");
    return 1;
  }
  int i = 0;
  while (strcmp(tokens[i]->id_pal, "EOF\0") != 0) {
    char *buf = malloc(32 * sizeof(char));
    char *aux1 = tokens[i]->id_pal;
    char *aux2 = tokens[i]->atribute;

    buf[0] = '<';

    int j = 0;
    while (aux1[j] != '\0') {
      buf[j + 1] = aux1[j];
      j++;
    }
    j++;
    buf[j] = ',';
    j++;
    buf[j] = ' ';
    j++;

    int k = 0;
    while (aux2[k] != '\0') {
      buf[j + k] = aux2[k];
      k++;
    }
    buf[j + k] = '>';
    k++;
    buf[j + k] = '\n';
    write(fd, buf, j + k);
  }

  if (close(fd) != 0) {
    printf("Error al cerrar");
    return 1;
  }
  return 0;
}
