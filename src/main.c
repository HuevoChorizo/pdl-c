#include "analizador.h"
#include "lector.h"
#include <stdio.h>
int main() {
  char **desglosado = lector();

  int funciona = analizador(desglosado);
  if (funciona == 0)
    printf("Funciona bien");

  else
    printf("No funciona");
  return funciona;
}
