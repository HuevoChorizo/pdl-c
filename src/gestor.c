#include "include/tokens.h"
#include <stdio.h>
#include <string.h>

char *tipoErr(int estado);

/*TODO: Este gestor imprime simplemente el error del analizador léxico,
 * después de la tabla de símbolos, el número de línea está en el propio
 * token de error, así como el estado en el cual se forma. */

/*NOTE: No estoy muy seguro de que el paso por la tabla sea necesario para
 * el analizador léxico, no me acuerdo bien de las funciones que cubre la
 * tabla de símbolos a la hora de realizar un análisis lexico-gráfico. */

/*NOTE: Tiene sentido pasar por aquí todos los tokens, o acaso solo mandarle
 * los tokens error tanto al gestor léxico como al semántico. */

int gestorLexico(tokens *tokens) {
  int i = 0;
  while (i < tokens->size) {
    if (strcmp(tokens->tokenArr[i].id_pal, "ERR") == 0) {
      /*TODO: definir un tamaño máximo*/
      char *salida_error;
    }
  }
  return 0;
}

int gestorSintactico(tokens *tokens) { return 0; }

char *tipoErr(int estado) {
  switch (estado) {
  case 1: {
  }
  case 2: {
  }
  case 3: {
  }
  case 4: {
  }
  case 5: {
  }
  case 6: {
  }
  }
  return "";
}
