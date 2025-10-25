#include "lector.h"
#include "procesador.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char **desglosado = lector();

  if (desglosado != NULL) {
    char **procesado = procesador(desglosado);

    if (procesado != NULL) {
      for (int i = 0; procesado[i] != NULL; i++) {
        printf("El token %d es el siguiente: %s \n", i, procesado[i]);
      }

      for (int i = 0; procesado[i] != NULL; i++) {
        free(procesado[i]);
      }
      free(procesado);
    } else {
      printf("Error: No se pudieron procesar los tokens.\n");
    }

    for (int i = 0; desglosado[i] != NULL; i++) {
      free(desglosado[i]);
    }
    free(desglosado);
  } else {
    printf("Error: No se pudo leer el archivo o procesar los datos.\n");
  }

  return 0;
}
