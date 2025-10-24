#include <stdlib.h>
#include <stdio.h>

//Inicializo los contadores para los valores de los atributos
int atr_OP=0;
int atr_PAL_RES=0;

//Estructura de los tokens
typedef struct token_s{
    char* id_pal;
    int atribute;
}token;

//El "constructor" de los tokens
token newToken(token* tok,char* id){
    tok->id_pal=id;
    switch('id'){
        case 'PAL_RES':
        tok->atribute=atr_OP++;
        break;
        case 'OP' :
        tok->atribute=atr_PAL_RES++;
        break;
        case 'EOF' :
        tok->atribute=0;
        break;
    }
}

//Un toString que no se si tendrá uso la verdad pero ahí esta mal hecho.
char* toString(token* tok){
    char* id = tok->id_pal;
    int atr= tok->atribute;
    char* res=  "<";
    int i=2;
    while(id[i]=='\0'){
        res=realloc(res,sizeof(char)*i);
        res[i-1]=id[i-2];
        i++;
    }
    res=realloc(res,sizeof(char)*(i+3));
    res[i+1]=' ';
    res[i+2]=',';
    res[i+3]=' ';
    res=realloc(res,sizeof(char)*(i+3)+sizeof(int));
    res[i+4]=atr;
    printf(res);
}

//Un boolean de si es válido el token o no
int estok_valido(token* aux_t){
    if(aux_t->id_pal==('PAL_RES'||'OP'||'EOF'))
        return 1;
    return 0;
}


