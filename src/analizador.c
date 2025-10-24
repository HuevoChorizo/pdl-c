#include "tokens.h"
#include <stdio.h>

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
      char aux = desglosado[i][k];
      char aux2 = desglosado[i][k + 1];
      if (aux == '(' || aux == ')' || aux == '"' ||
          (aux == '/' && aux2 == '*') || (aux == '*' &&))
        k++;
    }
  }

  return 0;
}
