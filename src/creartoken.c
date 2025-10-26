#include "procesador.h"
#include "tokens.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

token **crear(char **entrada) {
  token **res = malloc(200 * sizeof(token));
  int last_pos;
  int j = 0;
  for (int i = 0; entrada[i] != NULL && entrada[i][0] != '\0'; i++) {
    if (entrada[i][0] != '\0') {
      switch (entrada[i][0]) {
      case '=':
        res[j]->id_pal = "EQ";
        res[j]->atribute = "-";
        break;
      case ',':
        res[j]->id_pal = "COMA";
        res[j]->atribute = "-";
        break;
      case ';':
        res[j]->id_pal = "PUNTOCOMA";
        res[j]->atribute = "-";
        break;
      case '(':
        res[j]->id_pal = "PAROPEN";
        res[j]->atribute = "-";

        break;
      case ')':
        res[j]->id_pal = "PARCLOSE";
        res[j]->atribute = "-";

        break;
      case '{':
        res[j]->id_pal = "BROPEN";
        res[j]->atribute = "-";

        break;
      case '}':
        res[j]->id_pal = "BRCLOSE";
        res[j]->atribute = "-";

        break;
      case '+':
        res[j]->id_pal = "SUM";
        res[j]->atribute = "-";

        break;
      case '*':
        res[j]->id_pal = "MULT";
        res[j]->atribute = "-";

        break;
      case '/':
        res[j]->id_pal = "DIV";
        res[j]->atribute = "-";

        break;
      case '!':
        res[j]->id_pal = "NOT";
        res[j]->atribute = "-";

        break;
      case '<':
        res[j]->id_pal = "MENOS";
        res[j]->atribute = "-";

        break;
      case '>':
        res[j]->id_pal = "MAYOR";
        res[j]->atribute = "-";

        break;
      }
    } else if (entrada[i][1] != '\0') {
      switch (entrada[i][0]) {
      case '/':
        if (entrada[i][1] == '*') {
          res[j]->id_pal = "CBLOPEN";
          res[j]->atribute = "-";
        }
        break;
      case '*':
        if (entrada[i][1] == '/') {
          res[j]->id_pal = "CBLCLOSE";
          res[j]->atribute = "-";
        }
        break;
      // TODO: BORRAR ESTE CASE := JUNTO CON SU DESGLOSADO
      case ':':
        if (entrada[i][1] == '=') {
          res[j]->id_pal = "";
          res[j]->atribute = "-";
        }
        break;
      case '%':
        if (entrada[i][1] == '=') {
          res[j]->id_pal = "EQREST";
          res[j]->atribute = "-";
        }
        break;
      case '&':
        if (entrada[i][1] == '&') {
          res[j]->id_pal = "AND";
          res[j]->atribute = "-";
        }
        break;
      case '|':
        if (entrada[i][1] == '|') {
          res[j]->id_pal = "OR";
          res[j]->atribute = "-";
        }
        break;
      case '=':
        if (entrada[i][1] == '=') {
          res[j]->id_pal = "EQ";
          res[j]->atribute = "-";
        }
        break;
      }
    }

    if (strcmp(entrada[i], "boolean") == 0) {
      /*if (entrada[i + 2][1] != '=') {
        char *aux = tabla(entrada[i + 1], NULL);
      }
      char *aux = tabla(entrada[i + 1], entrada[i + 3]);
      Luego la tabla devuelve un char, con el identificador lo que sea.
      res[j]->id_pal = "ID";
      res[j]->atribute = aux;
      j++;
      TODO:Hay que convertir de int a String, o en su defecto hacer que la
       * tabla devuelva un String; también hay que aplicar esta lógica a toda
       * variable, para poder almacenarla en la tabla de símbolos, y al mismo
       * tiempo guardar su ID como un token.*/
      res[j]->id_pal = "BOOL";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "else") == 0) {
      res[j]->id_pal = "ELSE";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "float") == 0) {
      res[j]->id_pal = "FLOAT";
      res[j]->atribute = "-";
    }

    if (strcmp(entrada[i], "function") == 0) {
      res[j]->id_pal = "FUNCTION";
      res[j]->atribute = "-";
    }

    if (strcmp(entrada[i], "if") == 0) {
      res[j]->id_pal = "IF";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "read") == 0) {
      res[j]->id_pal = "READ";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "int") == 0) {
      res[j]->id_pal = "INT";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "let") == 0) {
      res[j]->id_pal = "LET";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "string") == 0) {
      res[j]->id_pal = "STR";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "void") == 0) {
      res[j]->id_pal = "VOID";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "write") == 0) {
      res[j]->id_pal = "WRITE";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "") == 0) {
      res[j]->id_pal = "";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "") == 0) {
      res[j]->id_pal = "";
      res[j]->atribute = "-";
    }
    if (strcmp(entrada[i], "") == 0) {
      res[j]->id_pal = "";
      res[j]->atribute = "-";
    }
    j++;
    last_pos = i;
  }
  /* Se añade EOF y se devuelve res */
  res[last_pos + 1]->atribute = "-";
  res[last_pos + 1]->id_pal = "EOF";
  res = realloc(res, sizeof(token) * (last_pos + 1));
  return res;
}
