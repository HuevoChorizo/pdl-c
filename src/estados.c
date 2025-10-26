#include "stdlib.h"
#include "tokens.h"
#include <ctype.h>
#define OK 0
#define ERR -1
#define EQ 1

/*TODO: Esto clasifica los tokens, se los manda a crear Token (hay que
 * modificarlo por completo, ahora mismo hace la función del autómata y de crear
 * tokens, solo tiene que hacer una de las dos.) y a la tabla de símbolos, se le
 * envía, desde el main un string de procesado a cada vez.*/
int estadoerr(char *palabra) { return -1; }
int estado4(char *palabra) {
  switch (palabra[0]) {
  case '=':
    return EQ;
    /*TODO: esto llama a crear token*/
    break;
  case ',':

    break;
  case ';':

    break;
  case '(':

    break;
  case ')':

    break;
  case '{':

    break;
  case '}':

    break;
  case '+':

    break;
  case '*':

    break;
  case '/':

    break;
  case '!':

    break;
  case '<':

    break;
  case '>':

    break;
  }
}
int estado5(char *palabra) {}

int estado1(char *palabra) {}

int estado2(char *palabra) {}

int estado3(char *palabra) {

  if (palabra[1] == '\0') {
    return estado4(palabra);
  } else if (palabra[2] == '\0') {
    return estado5(palabra);
  } else if (palabra[0] == '"') {
    return estado6(palabra);
  } else {
    return estadoerr(palabra);
  }
}

int estados(char **entrada) {
  int i = 0;
  int f = OK;
  /*Aquí se analiza el tipo de token, o los tokens en general.*/
  while (entrada[i] != NULL) {
    f = start(entrada[i]);
    i++;
  }
  /*TODO: Catchea errores, mandandolos a token con el id: ERR,
   * también tiene que comprender si es el comienzo de un string, o de un
   * comentario, o de un paréntesis de esta forma será más simple. esto procesa,
   * devuelve una señal, dependiendo de lo que surja, ponte por ejemplo que
   * detecte int como un token pues avisa de que el siguiente token tiene que
   * ser el nombre, al final del día va por estados lol */
  return 0;
}
int start(char *palabra) {
  if (isdigit(palabra[0])) {
    return estado1(palabra);
  } else if (isalpha(palabra[0])) {
    return estado2(palabra);
  } else {
    return estado3(palabra);
  }
  return OK;
}
