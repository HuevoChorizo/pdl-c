#include "procesador.h"
#include <stdlib.h>
#include <string.h>




int esToken(char** entrada){
    for(int i=0;entrada[i]!=NULL;i++){
        for(int j=0;'entrada[i][j]'!='\0';j++){
        if(entrada[i][j]!=NULL&& strcmp(entrada[i+1],NULL)==1){
            switch('entrada[i]'){
                case '=':
                
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
        }else{

        }

        }
    }
    return 0;
}