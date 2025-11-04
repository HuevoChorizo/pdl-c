#include "stdlib.h"
#include "tokens.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define OK 0
#define ERR -1
#define CMNTO 2
#define CMNTC 3
#define STR 4
#define ESPAL 5

int conT = 0;
token **resultado;

int estadoerr(char *palabra) {
  resultado[conT] = malloc(sizeof(token));
  resultado[conT]->id_pal = "ERR";
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  resultado[conT++]->atribute.cadena = cadena;
  return OK;
}

int estado4(char *palabra) {
  resultado[conT] = malloc(sizeof(token));
  switch (palabra[0]) {
  case '=':
    resultado[conT]->id_pal = "EQ";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case ',':
    resultado[conT]->id_pal = "COMA";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case ';':
    resultado[conT]->id_pal = "PUNTOCOMA";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '(':
    resultado[conT]->id_pal = "PAROPEN";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case ')':
    resultado[conT]->id_pal = "PARCLOSE";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '{':
    resultado[conT]->id_pal = "BROPEN";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '}':
    resultado[conT]->id_pal = "BRCLOSE";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '+':
    resultado[conT]->id_pal = "SUM";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '*':
    resultado[conT]->id_pal = "MULT";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '/':
    resultado[conT]->id_pal = "DIV";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '!':
    resultado[conT]->id_pal = "NOT";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '<':
    resultado[conT]->id_pal = "MENOS";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  case '>':
    resultado[conT]->id_pal = "MAYOR";
    resultado[conT++]->atribute.cadena = "-";
    return OK;
  }
  return estadoerr(palabra);
}

int estado5(char *palabra) {
  resultado[conT] = malloc(sizeof(token));
  switch (palabra[0]) {
  case '/':
    if (palabra[1] == '*') {
      resultado[conT]->id_pal = "CBLOPEN";
      resultado[conT++]->atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '*':
    if (palabra[1] == '/') {
      resultado[conT]->id_pal = "CBLCLOSE";
      resultado[conT++]->atribute.cadena = "-";
      return CMNTC;
    }
    return estadoerr(palabra);
  case '%':
    if (palabra[1] == '=') {
      resultado[conT]->id_pal = "EQresultadoT";
      resultado[conT++]->atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '&':
    if (palabra[1] == '&') {
      resultado[conT]->id_pal = "AND";
      resultado[conT++]->atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '|':
    if (palabra[1] == '|') {
      resultado[conT]->id_pal = "OR";
      resultado[conT++]->atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  case '=':
    if (palabra[1] == '=') {
      resultado[conT]->id_pal = "EQ";
      resultado[conT++]->atribute.cadena = "-";
      return OK;
    }
    return estadoerr(palabra);
  }
  return estadoerr(palabra);
}

int estado6(char *palabra) {
  if ((strlen(palabra) - 2) <= 64) {
    resultado[conT] = malloc(sizeof(token));
    resultado[conT]->id_pal = "str";
    resultado[conT++]->atribute.cadena = palabra;
    return OK;
  }
  return estadoerr(palabra);
}

int estado7(char *palabra) {
  float aux;
  resultado[conT] = malloc(sizeof(token));
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  sscanf(palabra, "%f", &aux);
  resultado[conT] = malloc(sizeof(token));
  resultado[conT]->id_pal = "CONSTFLOAT";
  resultado[conT]->atribute.valor = aux;
  resultado[conT++]->atribute.cadena = cadena;
  return OK;
}

int estado8(char *palabra) {
  int aux;
  resultado[conT] = malloc(sizeof(token));
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  sscanf(palabra, "%d", &aux);
  resultado[conT] = malloc(sizeof(token));
  resultado[conT]->id_pal = "CONSTINT";
  resultado[conT]->atribute.valor = aux;
  resultado[conT++]->atribute.cadena = cadena;
  return OK;
}

int estado9(char *palabra) {
  resultado[conT] = malloc(sizeof(token));
  char *cadena = malloc(strlen(palabra) + 1 * sizeof(char));
  memcpy(cadena, palabra, strlen(palabra) + 1);
  resultado[conT]->id_pal = "Var";
  resultado[conT++]->atribute.cadena = cadena;
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
  resultado[conT] = malloc(sizeof(token));

  if (strcmp(palabra, "boolean") == 0) {
    resultado[conT]->id_pal = "BOOL";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "else") == 0) {
    resultado[conT]->id_pal = "ELSE";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "float") == 0) {
    resultado[conT]->id_pal = "FLOAT";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "function") == 0) {
    resultado[conT]->id_pal = "FUNCTION";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "if") == 0) {
    resultado[conT]->id_pal = "IF";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "int") == 0) {
    resultado[conT]->id_pal = "INT";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "let") == 0) {
    resultado[conT]->id_pal = "LET";
    resultado[conT++]->atribute.cadena = "-";
  }
  if (strcmp(palabra, "read") == 0) {
    resultado[conT]->id_pal = "READ";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "return") == 0) {
    resultado[conT]->id_pal = "RET";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "string") == 0) {
    resultado[conT]->id_pal = "STR";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "void") == 0) {
    resultado[conT]->id_pal = "VOID";
    resultado[conT++]->atribute.cadena = "-";
    return ESPAL;
  }
  if (strcmp(palabra, "write") == 0) {
    resultado[conT]->id_pal = "WRITE";
    resultado[conT++]->atribute.cadena = "-";
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
  char *paso = malloc(64 * sizeof(char));
  int j = 0;
  int i = 0;
  while (palabra[i] != '\0') {
    if (isalnum(palabra[i]) || palabra[i] == '_' || palabra[i] == '.') {
      paso[j++] = palabra[i++];
    } else if (j != 0 && !isalnum(palabra[i + 1])) {
      paso[j] = '\0';
      flag = estado0(paso, flag);
      j = 0;
    } else if (palabra[i] == '/' && palabra[i + 1] == '*') {
      flag = estado3("/*");
      while (!(palabra[i] == '*' && palabra[i + 1] == '/')) {
        i++;
      }
      flag = estado3("*/");
      i = i + 2;
    } else if (palabra[i] == '"') {
      paso[j++] = palabra[i++];
      while (palabra[i] != '"') {
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
  }
  if (j != 0) {
    paso[j] = '\0';
    flag = estado0(paso, flag);
  }

  /*TODO: Este puntero hay que liberarlo y evitar enviarlo a otras zonas,
   * haciendo strcopy en vez de mandarlo directamente.*/
  return flag;
}

token **estados(char **palabra) {
  resultado = malloc(2000 * sizeof(token *));
  int i = 0;
  int f = OK;
  while (palabra[i] != NULL) {
    f = start(palabra[i], f);
    i++;
  }
  resultado[conT] = malloc(sizeof(token));
  resultado[conT]->id_pal = "EOF";
  resultado[conT]->atribute.cadena = "-";
  conT++;
  resultado = realloc(resultado, conT * sizeof(token *));
  return resultado;
}
