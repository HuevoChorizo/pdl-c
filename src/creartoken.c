#include "procesador.h"
#include <stdlib.h>
#include <string.h>
#include "tokens.h"




token** esToken(char** entrada){
    token** res=malloc(200*sizeof(token));
    int last_pos;
    for(int i=0;entrada[i]!=NULL&&entrada[i][0]!='\0';i++){
         if(entrada[i][0]!='\0'){
            switch(entrada[i][0]){
                 case '=':
                res[i]->id_pal="EQ";
                res[i]->atribute="-";
                break;
                 case ',':
                 res[i]->id_pal="COMA";
                res[i]->atribute= "-";
                break;
                 case ';':
                res[i]->id_pal="PUNTOCOMA";
                res[i]->atribute="-";
                break;
                 case '(':
                 res[i]->id_pal="PAROPEN";
                res[i]->atribute="-";

                break;
                 case ')':
                 res[i]->id_pal="PARCLOSE";
                res[i]->atribute="-";

                break;
                 case '{':
                 res[i]->id_pal="BROPEN";
                res[i]->atribute="-";

                break;
                 case '}':
                 res[i]->id_pal="BRCLOSE";
                res[i]->atribute="-";

                break;
                 case '+':
                 res[i]->id_pal="SUM";
                res[i]->atribute="-";

                break;
                 case '*':
                 res[i]->id_pal="MULT";
                res[i]->atribute="-";

                break;
                 case '/':
                 res[i]->id_pal="DIV";
                res[i]->atribute="-";

                break;
                 case '!':
                 res[i]->id_pal="NOT";
                res[i]->atribute="-";

                break;
                 case '<':
                 res[i]->id_pal="MENOS";
                res[i]->atribute="-";

                break;
                 case '>':
                 res[i]->id_pal="MAYOR";
                res[i]->atribute="-";

                break;
            }
        }else if(entrada[i][1]!='\0'){
            switch(entrada[i][0]){
                case '/':
                    if(entrada[i][1]=='*'){
                        res[i]->id_pal="CBLOPEN";
                        res[i]->atribute="-";
                    }
                break;
                case '*':
                    if(entrada[i][1]=='/'){
                        res[i]->id_pal="CBLCLOSE";
                        res[i]->atribute="-";
                    }
                break;
                //TODO: BORRAR ESTE CASE := JUNTO CON SU DESGLOSADO
                case ':':
                    if(entrada[i][1]=='='){
                        res[i]->id_pal="";
                        res[i]->atribute="-";
                    }
                break;
                case '%':
                    if(entrada[i][1]=='='){
                        res[i]->id_pal="EQREST";
                        res[i]->atribute="-";
                    }
                break;
                case '&':
                    if(entrada[i][1]=='&'){
                        res[i]->id_pal="AND";
                        res[i]->atribute="-";
                    }
                break;
                case '|':
                    if(entrada[i][1]=='|'){
                        res[i]->id_pal="OR";
                        res[i]->atribute="-";
                    }
                break;
                case '=':
                    if(entrada[i][1]=='='){
                        res[i]->id_pal="EQ";
                        res[i]->atribute="-";
                    }
                break;
            }
        

        }
        last_pos=i;
    }
    //AÑADO EL EOF Y RETURNEO RES
    res[last_pos+1]->atribute="-";
    res[last_pos+1]->id_pal="EOF";
    res=realloc(res,sizeof(token)*(last_pos+1));
    return res;
}