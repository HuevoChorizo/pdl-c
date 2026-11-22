#include "include/estados.h"
#include "include/lector.h"
#include "include/liberar.h"
#include "include/tabla.h"
#include "include/tokens.h"
#include "include/writer.h"

#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR -1
int liberar(tokens *a_liberar);

int main() {
  /*Simplifica el autómata, y la comprensión de lo que realiza.*/
  char **desglosado = lector();
  /*for (int i = 0; desglosado[i] != NULL; i++) {
    printf("La palabra nº: %d es: %s\n", i, desglosado[i]);
  } */
  tokens *a = estados(desglosado);

  if (a != NULL) {
    printf("El autómata funciona");
  }
  free(desglosado);
  int b = writer(a);

  liberar(a);

  /*TODO: Analizar a futuro si hay problemas con que el último elemento del
   * puntero sea NULL, si hay que quitarlo o que hacer. */

  return b;
}
/* NOTE: Esto es código espagueti en su máximo explendor, tengo que hacer una
 * función liberar.c*/
