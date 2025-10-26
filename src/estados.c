#include "stdlib.h"
#include "tokens.h"
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define OK 0
#define ERR -1
#define CMNTO 2
#define CMNTC 3
#define STR 4

int conT = 0;
token **resultado;

/*TODO: Esto clasifica los tokens, se los manda a crear Token (hay que
 * modificarlo por completo, ahora mismo hace la función del autómata y de crear
 * tokens, solo tiene que hacer una de las dos.) y a la tabla de símbolos, se le
 * envía, desde el main un string de procesado a cada vez.*/
int estadoerr(char *palabra) {
  resultado[conT]->id_pal = "ERR";
  resultado[conT]->atribute.cadena = palabra;
  return ERR;
}

int estado4(char *palabra) {
  switch (palabra[0]) {
  case '=':
    resultado[conT]->id_pal = "EQ";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case ',':
    resultado[conT]->id_pal = "COMA";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case ';':
    resultado[conT]->id_pal = "PUNTOCOMA";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '(':
    resultado[conT]->id_pal = "PAROPEN";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case ')':
    resultado[conT]->id_pal = "PARCLOSE";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '{':
    resultado[conT]->id_pal = "BROPEN";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '}':
    resultado[conT]->id_pal = "BRCLOSE";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '+':
    resultado[conT]->id_pal = "SUM";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '*':
    resultado[conT]->id_pal = "MULT";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '/':
    resultado[conT]->id_pal = "DIV";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '!':
    resultado[conT]->id_pal = "NOT";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '<':
    resultado[conT]->id_pal = "MENOS";
    resultado[conT]->atribute.cadena = "-";
    return OK;

  case '>':
    resultado[conT]->id_pal = "MAYOR";
    resultado[conT]->atribute.cadena = "-";
    return OK;
  }
  return estadoerr(palabra);
}

int estado5(char *palabra) {
  switch (palabra[0]) {
  case '/':
    if (palabra[1] == '*') {
      resultado[conT]->id_pal = "CBLOPEN";
      resultado[conT]->atribute.cadena = "-";
      return OK;
    }

  case '*':
    if (palabra[1] == '/') {
      resultado[conT]->id_pal = "CBLCLOSE";
      resultado[conT]->atribute.cadena = "-";
      return OK;
    }

  case '%':
    if (palabra[1] == '=') {
      resultado[conT]->id_pal = "EQresultadoT";
      resultado[conT]->atribute.cadena = "-";
      return OK;
    }

  case '&':
    if (palabra[1] == '&') {
      resultado[conT]->id_pal = "AND";
      resultado[conT]->atribute.cadena = "-";
      return OK;
    }

  case '|':
    if (palabra[1] == '|') {
      resultado[conT]->id_pal = "OR";
      resultado[conT]->atribute.cadena = "-";
      return OK;
    }

  case '=':
    if (palabra[1] == '=') {
      resultado[conT]->id_pal = "EQ";
      resultado[conT]->atribute.cadena = "-";
      return OK;
    }
  }
  return estadoerr(palabra);
}

int estado6(char *palabra, int f) {
  if ((strlen(palabra) - 2) <= 64) {
    resultado[conT]->id_pal = "str";
    resultado[conT]->atribute.cadena = palabra;
    return OK;
  }
  return estadoerr(palabra);
}

int estado1(char *palabra, int f) {}

int estado2(char *palabra, int f) {}

int estado3(char *palabra, int f) {
  if (palabra[1] == '\0') {
    return estado4(palabra);
  } else if (palabra[2] == '\0') {
    return estado5(palabra);
  } else if (palabra[0] == '"') {
    return estado6(palabra, f);
  } else {
    return estadoerr(palabra);
  }
}

int start(char *palabra, int f) {
  if (isdigit(palabra[0])) {
    return estado1(palabra, f);
  } else if (isalpha(palabra[0])) {
    return estado2(palabra, f);
  } else {
    return estado3(palabra, f);
  }
  return OK;
}
token **estados(char **palabra) {
  resultado = malloc(2000 * sizeof(token *));
  int i = 0;
  int f = OK;
  /*Aquí se analiza el tipo de token, o los tokens en general.*/
  while (palabra[i] != NULL) {
    i++;
    conT++;
  }
  return resultado;
}
/*TODO: Catchea erroresultado, mandandolos a token con el id: ERR,
 * también tiene que comprender si es el comienzo de un string, o de un
 * comentario, o de un paréntesis de esta forma será más simple. esto procesa,
 * devuelve una señal, dependiendo de lo que surconTa, ponte por econTemplo que
 * detecte int como un token pues avisa de que el siguiente token tiene que
 * ser el nombre, al final del día va por estados lol */
