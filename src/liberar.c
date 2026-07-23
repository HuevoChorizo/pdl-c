#include "include/liberar.h"
#include "include/tokens.h"
#include "stdlib.h"

/*TODO: hacer comprobaciones en los free; */

int liberar(tokens *a_liberar) {
  for (int i = 0; i < a_liberar->size - 2; i++) {
    int estado = a_liberar->tokenArr[i].estado;
    if ((estado == -1 || estado == 6 || estado == 7 || estado == 8 ||
         estado == 9) &&
        a_liberar->tokenArr[i].atribute.cadena != NULL)
      free(a_liberar->tokenArr[i].atribute.cadena);
  }
  free(a_liberar->tokenArr);
  free(a_liberar);
  return 0;
}
