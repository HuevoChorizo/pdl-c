#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tokens.h"
#include <string.h>

char** writer(){ 
    int fd=open("Mahjong_Soul",O_CREAT,O_WRONLY); 
    if(fd==-1){printf("Tonoto no sabe ejcribir archivos"); exit(1);}

    //TODO:token* buf=read(entrada_token) 
    token*buf;
    char* res='<';
    int cont_chartot=1;
    int cont_charman=0;
    while(buf->id_pal!='EOF'){
        //TODO: buf=READ(ENTRADA TOKEN) FALTA QUE VAYA METIENDO LO QUE APARECE DE LOS FICHEROS
        if(buf->id_pal=='PAL_RES'&&buf->atribute==0){ //si es el > termina y escribe
            write(fd,buf,sizeof(char)*cont_chartot);
            cont_charman=0; cont_chartot=0;
        }
        else if(cont_charman==0){
            res=realloc(res,sizeof(char)*(cont_chartot+strlen(buf->id_pal)));
            strcat(res,buf->id_pal);
            cont_charman+=strlen(buf->id_pal);
            cont_chartot+=cont_charman;
            res=realloc(res,sizeof(char)*(++cont_chartot));
            strcat(res,',');
        }
        else if(cont_charman!=0){
            res=realloc(res,sizeof(char)*(cont_charman+strlen(buf->atribute)+1));
            strcat(res,buf->atribute);
            strcat(res,buf->id_pal);
            cont_chartot+=strlen(buf->atribute)+1;
            cont_charman+=strlen(buf->atribute);
        }
        }
    }



