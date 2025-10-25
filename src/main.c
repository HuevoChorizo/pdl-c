#include "lector.h"
#include "procesador.h"
#include "tokens.h"
#include "writer.h"
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

    /*Prueba para comprobar si el writer funciona*/
    token **a = malloc(2 * sizeof(token *));
    if (a == NULL) {
      printf("Error al reservar memoria para los tokens\n");
      return 1;
    }

    a[0] = malloc(sizeof(token));
    if (a[0] == NULL) {
      printf("Error al reservar memoria para el primer token\n");
      free(a);
      return 1;
    }

    a[0]->id_pal = "BOOL";
    a[0]->atribute = "-";

    a[1] = malloc(sizeof(token));
    if (a[1] == NULL) {
      printf("Error al reservar memoria para el segundo token\n");
      free(a[0]);
      free(a);
      return 1;
    }
    a[1]->id_pal = "EOF";
    a[1]->atribute = NULL;

    if (writer(a) != 0) {
      printf("Hay un error en la escritura\n");
      free(a[0]);
      free(a[1]);
      free(a);
      return 1;
    }

    free(a[0]);
    free(a[1]);
    free(a);

    for (int i = 0; desglosado[i] != NULL; i++) {
      free(desglosado[i]);
    }
    free(desglosado);
  } else {
    printf("Error: No se pudo leer el archivo o procesar los datos.\n");
  }

  return 0;
}
