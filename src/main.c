#include "analizador.h"
#include "lector.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
  char **desglosado = lector();

  int funciona = analizador(desglosado);
  if (funciona == 0)
    printf("Funciona bien");

  else
    printf("No funciona");

  for (int i = 0; desglosado[i] != NULL; i++) {
    free(desglosado[i]);
  }
  free(desglosado);
  return funciona;
}
