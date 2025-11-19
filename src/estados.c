#include "tokens.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OK 0
#define ERR -1
#define CMNTO 2
#define CMNTC 3
#define STR 4
#define ESPAL 5

int conT = 0;
int conTLin = 0;

tokens *resultado;

int estadoerr(char *palabra) {
  resultado->tokenArr[conT].id_pal = "ERR";
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  resultado->tokenArr[conT++].atribute.cadena = cadena;
  return OK;
}

int estado4(char *palabra) {
  switch (palabra[0]) {
  case '=':
    resultado->tokenArr[conT].id_pal = "EQ";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case ',':
    resultado->tokenArr[conT].id_pal = "COMA";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case ';':
    resultado->tokenArr[conT].id_pal = "PUNTOCOMA";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '(':
    resultado->tokenArr[conT].id_pal = "PAROPEN";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case ')':
    resultado->tokenArr[conT].id_pal = "PARCLOSE";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '{':
    resultado->tokenArr[conT].id_pal = "BROPEN";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '}':
    resultado->tokenArr[conT].id_pal = "BRCLOSE";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '+':
    resultado->tokenArr[conT].id_pal = "SUM";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '*':
    resultado->tokenArr[conT].id_pal = "MULT";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '/':
    resultado->tokenArr[conT].id_pal = "DIV";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '!':
    resultado->tokenArr[conT].id_pal = "NOT";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '<':
    resultado->tokenArr[conT].id_pal = "MENOS";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  case '>':
    resultado->tokenArr[conT].id_pal = "MAYOR";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return OK;
  }
  return estadoerr(palabra);
}

int estado5(char *palabra) {
  switch (palabra[0]) {
  case '/':
    if (palabra[1] == '*') {
      resultado->tokenArr[conT].id_pal = "CBLOPEN";
      resultado->tokenArr[conT++].atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '*':
    if (palabra[1] == '/') {
      resultado->tokenArr[conT].id_pal = "CBLCLOSE";
      resultado->tokenArr[conT++].atribute.cadena = "-";
      return CMNTC;
    }
    return estadoerr(palabra);
  case '%':
    if (palabra[1] == '=') {
      resultado->tokenArr[conT].id_pal = "EQresultadoT";
      resultado->tokenArr[conT++].atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '&':
    if (palabra[1] == '&') {
      resultado->tokenArr[conT].id_pal = "AND";
      resultado->tokenArr[conT++].atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '|':
    if (palabra[1] == '|') {
      resultado->tokenArr[conT].id_pal = "OR";
      resultado->tokenArr[conT++].atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '=':
    if (palabra[1] == '=') {
      resultado->tokenArr[conT].id_pal = "EQ";
      resultado->tokenArr[conT++].atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  }
  return estadoerr(palabra);
}

int estado6(char *palabra) {
  if ((strlen(palabra) - 2) <= 64) {
    char *cadena = malloc(strlen(palabra) + 1);
    memcpy(cadena, palabra, strlen(palabra) + 1);
    resultado->tokenArr[conT].id_pal = "str";
    resultado->tokenArr[conT++].atribute.cadena = cadena;
    return OK;
  }
  return estadoerr(palabra);
}

int estado7(char *palabra) {
  float aux;
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  sscanf(palabra, "%f", &aux);
  resultado->tokenArr[conT].id_pal = "CONSTFLOAT";
  resultado->tokenArr[conT].atribute.valor = aux;
  resultado->tokenArr[conT++].atribute.cadena = cadena;
  return OK;
}

int estado8(char *palabra) {
  int aux;
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  sscanf(palabra, "%d", &aux);
  resultado->tokenArr[conT].id_pal = "CONSTINT";
  resultado->tokenArr[conT].atribute.valor = aux;
  resultado->tokenArr[conT++].atribute.cadena = cadena;
  return OK;
}

int estado9(char *palabra) {
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  resultado->tokenArr[conT].id_pal = "Var";
  resultado->tokenArr[conT++].atribute.cadena = cadena;
  return OK;
}

int estado1(char *palabra, int f) {
  if (f == ESPAL) {
    return estado9(palabra);
  }

  int j = 0;
  int esFloat = 0;
  while (palabra[j] != '\0') {
    if (palabra[j] == '.') {
      esFloat = 1;
      if (!(isdigit(palabra[j + 1])))
        return estadoerr(palabra);
    } else if (!(isdigit(palabra[j])) && (palabra[j] == '.' && esFloat == 1))
      return estadoerr(palabra);
    j++;
  }
  if (esFloat) {
    return estado7(palabra);
  }
  return estado8(palabra);
}

int estado2(char *palabra, int f) {

  if (strcmp(palabra, "boolean") == 0) {
    resultado->tokenArr[conT].id_pal = "BOOL";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "else") == 0) {
    resultado->tokenArr[conT].id_pal = "ELSE";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "float") == 0) {
    resultado->tokenArr[conT].id_pal = "FLOAT";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "function") == 0) {
    resultado->tokenArr[conT].id_pal = "FUNCTION";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "if") == 0) {
    resultado->tokenArr[conT].id_pal = "IF";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "int") == 0) {
    resultado->tokenArr[conT].id_pal = "INT";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "let") == 0) {
    resultado->tokenArr[conT].id_pal = "LET";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "read") == 0) {
    resultado->tokenArr[conT].id_pal = "READ";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "return") == 0) {
    resultado->tokenArr[conT].id_pal = "RET";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "string") == 0) {
    resultado->tokenArr[conT].id_pal = "STR";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "void") == 0) {
    resultado->tokenArr[conT].id_pal = "VOID";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "write") == 0) {
    resultado->tokenArr[conT].id_pal = "WRITE";
    resultado->tokenArr[conT++].atribute.cadena = "-";
    return ESPAL;
  }
  if (f == ESPAL) {
    return estado9(palabra);
  }
  if (f == CMNTO) {
    return OK;
  }
  return estadoerr(palabra);
}

int estado3(char *palabra) {
  if (palabra[1] == '\0') {
    if (palabra[0] == '\n') {
      conTLin++;
      return OK;
    }
    return estado4(palabra);
  } else if (palabra[2] == '\0') {
    return estado5(palabra);
  } else if (palabra[0] == '"') {
    return estado6(palabra);
  } else {
    return estadoerr(palabra);
  }
}
/*Manda palabras a estado 1 y números a estado 2*/
int estado0(char *palabra, int f) {
  if (isalpha(palabra[0]))
    return estado2(palabra, f);
  return estado1(palabra, f);
}
int start(char *palabra, int f) {
  int flag = f;
  if (flag == CMNTC)
    flag = OK;
  char *paso = malloc((strlen(palabra) + 1) * sizeof(char));
  int j = 0;
  int i = 0;
  while (palabra[i] != '\0') {
    if (isalnum(palabra[i]) || palabra[i] == '_' || palabra[i] == '.') {
      paso[j++] = palabra[i++];
    } else if (j != 0 && !isalnum(palabra[i])) {
      paso[j] = '\0';
      flag = estado0(paso, flag);
      j = 0;
    } else if (palabra[i] == '/' && palabra[i + 1] == '*') {
      flag = estado3("/*");
      while (!(palabra[i] == '*' && palabra[i + 1] == '/')) {
        if (palabra[i] == '\n')
          conTLin++;
        i++;
      }
      flag = estado3("*/");
      i = i + 2;
    } else if (palabra[i] == '"') {
      paso[j++] = palabra[i++];
      while (palabra[i] != '"' || (i != 0 && palabra[i - 1] == '\\')) {
        paso[j++] = palabra[i++];
      }
      paso[j++] = palabra[i];
      paso[j] = '\0';
      flag = estado6(paso);
      j = 0;
      i++;
    } else if (palabra[i + 1] != '\0') {
      if (!isalnum(palabra[i + 1]) && palabra[i + 1] != '"' &&
          !(palabra[i + 1] == '/' && palabra[i + 2] == '*')) {
        if (palabra[i + 1] != '(' && palabra[i + 1] != ')') {
          char mandar[3];
          mandar[0] = palabra[i++];
          mandar[1] = palabra[i++];
          mandar[2] = '\0';
          flag = estado3(mandar);
        } else {
          char mandar[2];
          mandar[0] = palabra[i++];
          mandar[1] = '\0';
          flag = estado3(mandar);
        }

      } else if (flag != CMNTC) {
        char mandar[2];
        mandar[0] = palabra[i++];
        mandar[1] = '\0';
        flag = estado3(mandar);
      }
    } else if (flag != CMNTC) {
      char mandar[2];
      mandar[0] = palabra[i++];
      mandar[1] = '\0';
      flag = estado3(mandar);
    }
  }
  if (j != 0) {
    paso[j] = '\0';
    flag = estado0(paso, flag);
  }

  /*TODO: Este puntero hay que liberarlo y evitar enviarlo a otras zonas,
   * haciendo strcopy en vez de mandarlo directamente.*/
  free(paso);
  free(palabra);
  return flag;
}

tokens *estados(char **palabra) {
  resultado = malloc(sizeof(tokens));
  resultado->tokenArr = malloc(200000);
  int i = 0;
  int f = OK;
  while (palabra[i] != NULL) {
    f = start(palabra[i], f);
    i++;
  }
  resultado->tokenArr[conT].id_pal = "EOF";
  resultado->tokenArr[conT++].atribute.cadena = "-";
  resultado->size = conT;

  resultado->tokenArr = realloc(resultado->tokenArr, (conT * sizeof(token)));
  return resultado;
}
