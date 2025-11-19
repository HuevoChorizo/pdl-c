#ifndef TOKENS_H
#define TOKENS_H

typedef union atributo {
  char *cadena;
  double valor;
} atrib;

typedef struct token_s {
  char *id_pal;
  atrib atribute;
} token;
typedef struct {
  token *tokenArr;
  int size;
} tokens;

#endif
