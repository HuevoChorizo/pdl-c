#include "estados.h"
#include "lector.h"
#include "tokens.h"
#include "writer.h"
#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR -1

int main() {
  /*Simplifica el autómata, y la comprensión de lo que realiza.*/
  char **desglosado = lector();
  token **a = estados(desglosado);
  if (a != NULL) {
    printf("El autómata funciona");
  }
  writer(a);
  /*Aquí se liberan los punteros.*/

  /*TODO: Analizar a futuro si hay problemas con que el último elemento del
   * puntero sea NULL, si hay que quitarlo o que hacer. */
  for (int i = 0; desglosado[i] != NULL; i++) {
    free(desglosado[i]);
  }
  free(desglosado);
  return 0;
}
