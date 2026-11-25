#include "include/lector.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char *p;

int lectornuevo(char *ruta, char *palabra, int *pipe) {
  /*TODO: falta la gestión de la pipe, pero me da pereza*/
  struct stat bstat;

  int fd = open(ruta, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Error al abrir el fichero\n");
    return (LECT);
  }

  fstat(fd, &bstat);
  p = mmap(NULL, bstat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  /*TODO: comprobar la apertura del mapa correcta*/
  if (close(fd) != 0) {
    fprintf(stderr, "El fichero se ha cerrado con error\n");
    return (CRRDO);
  }

  char *aux;
  /*TODO: Igual aloco aux con un tam max de bstat.st_size, pero creo que sería
   * muy esquizo.
   * Igual no tiene mucho sentido, puesto que con el memcpy solo copio lo
   * necesario. pero weno, ya veremos*
   * */

  int i = 0;
  while (i < bstat.st_size) {

    int j = func(i, aux);
    memcpy(palabra, aux, j);
    /*NOTE: manda enteros de forma temporal, el formato aún no se ha definido.*/
    write(pipe[1], 0, sizeof(int));
    read(pipe[0], NULL, sizeof(int));
    i += j;
    /*TODO: mandar una señal EOF o algo para indicar que no espere más
     * palabras*/
  }
  free(aux);
  munmap(p, bstat.st_size);
  /*TODO: comprobar el correcto cierre del mapa*/

  return OK;
}

/*NOTE: devuelve la diferencia*/
/*NOTE: Tiene que copiar la funcionalidad del bucle de lector.*/
/*TODO: Cambiar char *aux por un struct que contenga nº Línea, pos y el string*/
int func(int i, char *aux) {
  /*TODO: quizá, cambiar numLinea y posLinea, para que sean globales. */
  int numLinea;
  int posLinea;
  int j = 0;
  int k = 0;
  int s = 0;
  int cb = 0;
  int f = 0;

  while (!f) {
    if (s || p[i + j] == '\'') {
      if (p[i + j] == '\'' && i != 0 && s == 1) {
        s = 0;
        f = 1;

      } else if (p[i + j + 2] == '\0') {
        s = 0;
        aux[k++] = '\'';
        aux[k++] = 'N';
        aux[k++] = '\0';
        f = 1;
      } else {
        s = 1;
      }
      aux[k++] = p[i + j++];
      posLinea++;
      /*TODO: Gestionar saltos de línea dentro de los comentarios de bloque,
       * para seguir aumenta las líneas, a medida que hay saltos en el CB.*/
    } else if (cb || (p[i + j] == '/' && p[i + j] == '*')) {
      if (p[i + j++] == '\n') {
        numLinea++;
        posLinea = 0;
      }
      if (p[i + j] == '*' && p[i + j + 1] == '/') {
        cb = 0;
        f = 1;
      } else if (p[i + j + 1] == '\0' || p[i + j + 2] == '\0') {
        aux[k++] = '*';
        aux[k++] = '/';
        aux[k++] = 'N';
        aux[k++] = '\0';
        cb = 0;
        f = 1;
      } else {
        cb = 1;
      }
      aux[k++] = p[i + j++];
      posLinea++;
      if (!cb) {
        aux[k++] = p[i + j++];
        posLinea++;
      }

    } else if (p[i + j] == '\t') {
      aux[k] = '\0';
      f = 1;
      j++;
      posLinea++;
    } else if (p[i + j] == ' ') {
      aux[k] = '\0';
      f = 1;
      j++;
      posLinea++;
    } else if (p[i + j] == '\n') {
      aux[k] = '\0';
      f = 1;
      numLinea++;
    } else {
      aux[k++] = p[i + j++];
      posLinea++;
    }
  }
  /*TODO: asignar posLinea y numLinea a los atributos del struct. */
  return j;
}
