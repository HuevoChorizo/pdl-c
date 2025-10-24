#ifndef TOKENS_C
#define TOKENS_C

typedef struct token_s{
    char* id_pal;
    int atribute;
}token;

token newToken(token* tok,char* id);
char* toString(token* tok);
int estok_valido(token* tok);

#endif  








