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
  free(desglosado);
  int b = writer(a);

  /*TODO: Analizar a futuro si hay problemas con que el último elemento del
   * puntero sea NULL, si hay que quitarlo o que hacer. */
  for (int i = 0; a[i] != NULL; i++) {
    free(a[i]);
  }

  free(a);
  return b;
}
