#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* procesa el fichero desglosado en segmentos a evaluar posteriormente */
char **procesador(char **desglosado) {
  char **procesado = malloc(200 * sizeof(char *));
  if (procesado == NULL) {
    printf("Error al reservar memoria para procesado\n");
    exit(1);
  }

  int i = 0;
  int j = 0;
  while (desglosado[i] != NULL) {
    int k = 0;
    int segmento = 0;

    while (desglosado[i][k] != '\0') {
      char aux = desglosado[i][k];
      char aux1 = desglosado[i][k + 1];

      /* Hay que incluir otro tipo de caracteres especiales, para evitar
       * problemas, vaya. */
      if ((aux == '/' && aux1 == '*') || (aux == '*' && aux1 == '/') ||
          (aux == ':' && aux1 == '=') || (aux == '%' && aux1 == '=') ||
          (aux == '&' && aux1 == '&') || (aux == '|' && aux1 == '|') ||
          (aux == '=' && aux1 == '=')) {

        /* Si hay un token antes, lo guardamos */
        if (k > 0) {
          char *introducir = malloc((k - segmento + 1) * sizeof(char));
          if (introducir == NULL) {
            printf("Error al reservar memoria para token\n");
            exit(1);
          }
          strncpy(introducir, desglosado[i] + segmento, k - segmento);
          introducir[k - segmento] = '\0';
          procesado[j++] = introducir;
        }

        /* Creamos el operador de dos caracteres */
        char *aux2 = malloc(3 * sizeof(char));
        aux2[0] = aux;
        aux2[1] = aux1;
        aux2[2] = '\0';
        procesado[j++] = aux2;
        segmento = k + 2;
        k++;
      } else if (aux == '=' || aux == ',' || aux == ';' || aux == '(' ||
                 aux == ')' || aux == '{' || aux == '}' || aux == '+' ||
                 aux == '*' || aux == '/' || aux == '!' || aux == '<' ||
                 aux == '>') {

        /* Si hay un token antes, lo guardamos */
        if (k > 0) {
          char *introducir = malloc((k - segmento + 1) * sizeof(char));
          if (introducir == NULL) {
            printf("Error al reservar memoria para token\n");
            exit(1);
          }
          strncpy(introducir, desglosado[i] + segmento, k - segmento);
          introducir[k - segmento] = '\0';
          procesado[j++] = introducir;
        }

        /* Creamos el operador de un solo carácter */
        char *aux2 = malloc(2 * sizeof(char));
        aux2[0] = aux;
        aux2[1] = '\0';
        procesado[j++] = aux2;
        segmento = k + 1;
      }

      k++;
    }

    /* Si hay un token restante al final de la cadena, lo guardamos */
    if (desglosado[i][k] == '\0' && k > segmento) {
      char *introducir = malloc((k - segmento + 1) * sizeof(char));
      if (introducir == NULL) {
        printf("Error al reservar memoria para último token\n");
        exit(1);
      }
      strncpy(introducir, desglosado[i] + segmento, k - segmento);
      introducir[k - segmento] = '\0';
      procesado[j++] = introducir;
    }

    i++;
  }

  procesado[j] = NULL;
  return procesado;
}
