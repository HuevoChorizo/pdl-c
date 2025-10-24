#include <stdlib.h>




typedef struct token_s{
    char* id_pal;
    int atribute;
}token;

void inittoken(token* tok){
    tok->id_pal;
    tok->atribute;
}


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
}
