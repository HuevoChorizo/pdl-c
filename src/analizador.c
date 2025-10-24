#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

/*Esto básicamente se podría pasar a otro fichero, por ejemplo comprobar.c, pero
 * de momento, como estoy probando no me apetece.*/
int comprobar(char *agrupacion) { return 0; }

int analizador(char **desglosado) {
  token *tokens;
  if (desglosado == NULL)
    return 1;

  int i = 0;
  int j = 0;
  while (desglosado[i] != NULL) {
    /*TODO: inicializar tokens*/
    if (comprobar(desglosado[i]) == 0) {
      /* No sé si hacer aquí el "tokenificador, o en otro fichero, está por
       * verse, pero vaya, que simplemente transforma una palabra reservada, un
       * operador, un comparador o lo que sea en su código de token según la
       * tabla, vaya que es un switch de verdad "*/
      tokens[j].id_pal = desglosado[i];
      j++;
    }

    /*Esto quizás era más preciso hacerlo en lector, pero llevaría más tiempo,
     * pues recorrería todos los caracteres de forma innecesaria analizandolos,
     * y si ya hay una agrupación que se puede definir como un token, o una
     * palabra reservada de primeras, perderíamos tiempo.*/
    int k = 0;
    while (desglosado[i][k] != '\0') {
      int encontrado = 0;
      char aux = desglosado[i][k];
      char aux1 = desglosado[i][k + 1];
      if ((aux == '/' && aux1 == '*') || (aux == '*' && aux1 == '/') ||
          (aux == '%' && aux1 == '=') || (aux == '&' && aux1 == '&') ||
          (aux == '|' && aux1 == '|') || (aux == '=' && aux1 == '=')) {
        char *aux2 = malloc(3 * sizeof(char));
        aux2[0] = aux;
        aux2[1] = aux1;
        aux2[2] = '\0';
        tokens[j].id_pal = aux2;
        encontrado = 1;
        free(aux2);
      } else if (aux == '=' || aux == ',' || aux == ';' || aux == '(' ||
                 aux == ')' || aux == '{' || aux == '}' || aux == '+' ||
                 aux == '*' || aux == '/' || aux == '!' || aux == '<' ||
                 aux == '>') {
        char *aux2 = malloc(2 * sizeof(char));
        aux2[0] = aux;
        aux2[1] = '\0';
        tokens[j].id_pal = aux2;
        free(aux2);
        encontrado = 1;
      }
      int l = 0;
      while (encontrado) {

        encontrado = 0;
      }

      k++;
    }
  }

  return 0;
}
